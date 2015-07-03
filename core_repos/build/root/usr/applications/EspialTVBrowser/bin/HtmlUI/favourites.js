
/*
 * Implementation of the BookmarkFlow class.
 *
 * inputList - a HTML list element, used as content input for the bookmark 
 * bookmarkArea - a HTML div element that will hold the DOM structure of the bookmark.
 */ 
function BookmarkFlow(inputList, bookmarkArea) {
	
	/***** SETTINGS  - Change these values to alter the look and feel of the bookmark. *******/

	this.bookmarkMaxWidth = 0;			// Maximum Size of the bookmark area. 0 values means there's no limit (= fit to screen)
	this.bookmarkMaxHeight = 0;			//   Note: 	Size is adjusted to fit inside the browser window, if these max values are larger than window size.
	
	this.magnifireWidth  = 200;			// Position and size od the magnifire 
	this.magnifireHeight = 150;	
	this.magnifirePosX   = 350;
	this.magnifirePosY   = 250;	
	this.magnifirePadding= 10;			// Padding between the magnifire and it's content (the selected thumbnail)

	this.menuFlowSpeed = 0.5;			// Flow speed for flowing the menu items UP/DOWN in one step (in seconds)
	this.thumbFlowSpeed = 0.4;			// Flow speed for flowing the thumbnails LEFT/RIGHT in one step (in seconds)	
	this.thumbShowSpeed = 0.4;			// Speed for showing the new row of thumbnails when flowing UP/DOWN (in seconds)

	this.opacStartValue = 0.65;			// Opacity value for the first menu item that is not selected 
	this.opacStepValue = 0.17;			// Opacity value step between each menu item that are not selected
		
	/***** Constants *****/
	this.UP = -1;
	this.DOWN = 1;
	this.LEFT = -2;
	this.RIGHT = 2;
	this.resPath = "Res/";				// Path of resources (thumbnails, images)
	
	/***** Fields ********/
	this.bookmarkArea = bookmarkArea;	// Container 'div'
	this.MenuFlow;						// MenuFlow object	
	this.ThumbFlows = [];				// Array of ThumbFlow objects
		
	/***** Public API's *****/

	// Update the UI
	this.update = function() {
	 	// update menu flow
		this.MenuFlow.update();
		// update each thumbflow
		
		for (var i = 0; i < this.ThumbFlows.length; i++)
		{
		 	this.ThumbFlows[i].hide();
			this.ThumbFlows[i].update();
			
		}
		// Show thumbnails of selected menu item
		var index = this.MenuFlow.getSelectedIndex();
		if (index < this.ThumbFlows.length)
			this.ThumbFlows[index].show();
			
	}
	// Flow items as requested
	this.flow = function(dir) {
	 	if (dir == this.UP || dir == this.DOWN)				// flowing the menu items UP/DOWN
	 	{
	 	 	oldInd = this.MenuFlow.getSelectedIndex();
			this.MenuFlow.flow(dir);
			newInd = this.MenuFlow.getSelectedIndex();
			if (oldInd != newInd)							// Hide prev thumnails, and show the new ones
			{
				if (oldInd < this.ThumbFlows.length)
					this.ThumbFlows[oldInd].hide();
				if (newInd < this.ThumbFlows.length)
					this.ThumbFlows[newInd].show();	
			}
		}
		else if (dir == this.LEFT || dir == this.RIGHT)		// flowing the thumnails LEFT/RIGHT
		{
			dir = dir/2;	// we need values of -1 and 1
			var index = this.MenuFlow.getSelectedIndex();
			if (index < this.ThumbFlows.length)
				this.ThumbFlows[index].flow(dir);
		}
	}	
	// Load the selected page
	this.loadSelection = function() {
		var index = this.MenuFlow.getSelectedIndex();
		if (index < this.ThumbFlows.length)
			this.ThumbFlows[index].load();
	}
	
	/***** Initialization **/

	// Set size of the bookmark area. Note: As we don't want any scrolling, size should be inside browser window boundries.
	if (this.bookmarkMaxWidth > 0)
		this.bookmarkArea.style.width = Math.min(this.bookmarkMaxWidth, window.innerWidth) + "px";
	else
		this.bookmarkArea.style.width = window.innerWidth + "px";
	if (this.bookmarkMaxHeight > 0)
		this.bookmarkArea.style.height = Math.min(this.bookmarkMaxHeight, window.innerHeight) + "px";
	else
		this.bookmarkArea.style.height = window.innerHeight + "px";

	// Creating the magnifire
	var magn = document.createElement('div');
	if (magn) {
		magn.setAttribute("id", "magnifire");		
		magn.style.left = this.magnifirePosX + "px";
		magn.style.top  = this.magnifirePosY + "px";
		magn.style.width  = this.magnifireWidth + "px";
		magn.style.height = this.magnifireHeight + "px";
		this.bookmarkArea.appendChild(magn);
	}
	
	// Creating the MenuFlow object
	this.MenuFlow = new MenuFlow(this, inputList);

	// Parsing input and Creating the list of ThumbFlow objects	
	for (var i = 0; i < inputList.childNodes.length; i++)
		if (inputList.childNodes[i].nodeName == "LI")		// this is 'folder-name'
		{
		 	// find 'UL' element (sublist)
		 	var sublistEl = null;
		 	litem = inputList.childNodes[i];
		 	for (var j = 0; j < litem.childNodes.length; j++)
		 		if (litem.childNodes[j].nodeName == "UL")	// sublist found
		 			sublistEl = litem.childNodes[j];

		 	// create ThumbFlow object based on this sublist
		 	var thumbFlowObj = new ThumbFlow(this, sublistEl);
		 	this.ThumbFlows.push(thumbFlowObj);
		}
	
}	// end of MenuBookmarkFlow class



/*
 * Implementation of the MenuFlow class
 * Used by the BookmarkFlow class to flow menu items vertically in the bookmark area.
 *
 * owner - the BookmarkFlow object containing this menuflow
 * inputList - a HTML list element, used for input (the class uses the text value from the top level 'li' tags)
 */
function MenuFlow(owner, inputList)
{
	/***** Settings  *******/

	this.itemHeight = 35;			// Height of an item in the vertical list
	this.selItemIndent = -15;		// X-Indent of the selected item, compared to the others
	this.selPaddingTop = 20;		// Distance between the selected menu item and the rest above	
	this.selPaddingBottom = 0;		// Distance between the selected menu item and the magnifire.
	this.padMagnifireDown = 40;		// Distance between magnifire and menu item below

	/***** Fields ********/	
	this.owner = owner;				// The BookmarkFlow object containing this menuflow	
	this.items = [];				// Array of MenuItem objects
	this.selectedIndex = 0;			// Index of the item being selected
	
	/***** Public API's *****/
	
	// Get the index of the selected MenuItem 
	this.getSelectedIndex = function ()	{
		return this.selectedIndex;	
	}
 	// Updating position of items (= set new positions for each item by CSS styling, animation is handled by CSS)
	this.update = function ()
	{		
		for (i = 0; i < this.items.length; i++)		/* update each cover item */
			this.items[i].update();
	};
	// Scroll menu items to the new position
	this.flowTo = function (newIndex)
	{	 
		newIndex = Math.max(newIndex, 0);
		newIndex = Math.min(newIndex, this.items.length - 1);
		this.selectedIndex = newIndex;
		this.update();
	};
	// Scroll items up/down with 'step' steps. Positive or Negative values decide direction.
	this.flow = function(step) {
		this.flowTo(this.selectedIndex + step);
	};
		
	/***** Initialization **/
	
	/* Fill array of menu items and add created DOM elements to the holder div */
	var child;
	var index = 0;
	for (var i = 0; i < inputList.childNodes.length; i++)
		if (inputList.childNodes[i].nodeName == "LI")
		{
		 	var item = new MenuItem(this, index, inputList.childNodes[i]);
			this.items.push(item);
			this.owner.bookmarkArea.appendChild(item.itemDiv);
			index++;
		}
	
}	// end of MenuFlow class


/* 
 * Implementation of the MenuItem class
 * Used by the MenuFlow class to create its elements.
 *
 * menuFlowObj - the parent object (menu to which the item belongs)
 * ind - index of this item in the menu
 * element - html 'li' element from which the item is created (item uses the text value from the 'LI' element, which is a picture file name, that has to be displayed)
 */
function MenuItem(menuFlowObj, ind, element){

	/***** Fields ********/	
	this.menu = menuFlowObj;
	this.index = ind;

	/***** Public API's *****/

	/* Update this items position, based on the selected index in the menu (owner) */
	this.update = function() {				

		/* X coordinate */
		var xposnew = 0;		
		if (this.index != this.menu.selectedIndex)
			xposnew	= this.menu.owner.magnifirePosX - this.menu.selItemIndent;
		else
			xposnew = this.menu.owner.magnifirePosX;

		/* calculate Y coordinate */
		var offset = this.index - this.menu.selectedIndex;		
		var yposnew = this.menu.owner.magnifirePosY - this.menu.itemHeight				// position of selected item
						+ this.menu.itemHeight * (offset);							// + y offset of this item	
		// some adjusments
		if (offset > 0)			// items below the selected item are shifted, to make place for the magnifire
			yposnew += this.menu.owner.magnifireHeight + this.menu.padMagnifireDown;
		else if (offset < 0)	// items above the selected item are shifted further
			yposnew -= this.menu.selPaddingTop;
		else					// selected item can be closer/further from magnifire
			yposnew += this.menu.selPaddingBottom;
		
		/* opacity */
		var opnew = 1;
		if (offset != 0)		// calculate opacity for items not selected
			opnew = Math.max(0, this.menu.owner.opacStartValue - ((Math.abs(offset)-1)* this.menu.owner.opacStepValue));
		
		/* Set new values */
		if (opnew > 0 || this.itemDiv.style.webkitTransform == "")			// there's no sense to move invisible element :)
			this.itemDiv.style.webkitTransform='translate('+xposnew+'px, '+yposnew+'px) ';			
		this.itemDiv.style.opacity = opnew;
	};

	/***** Initialization **/
	
	// Creating the menu item div, holding one item (text or image) */
	this.itemDiv = document.createElement("div");
	if (this.itemDiv)
	{
		this.itemDiv.setAttribute("class", "menuItem");
		this.itemDiv.style.height = this.menu.itemHeight + "px";
		this.itemDiv.style.webkitTransform = "";
//		this.itemDiv.style.WebkitTransition = "all "+this.menu.owner.menuFlowSpeed+"s ease-in-out";
		if (element.childNodes.length >0)
		{
		 	// add image
			var img = document.createElement("img");
			img.setAttribute("src", this.menu.owner.resPath + element.childNodes[0].nodeValue);
			this.itemDiv.appendChild(img);
		}
	}
	
}	// end of MenuItem class



/*
 * Implementation of the ThumbFlow class
 * Used by the BookmarkFlow class to flow thumbnails horizontally the bookmark area.
 *
 * owner - the BookmarkFlow object containing this thumbnail flow
 * inputList - a HTML list element, used for input (each 'li' should have 2 'span' tags, with the thumbail data: name, picturename, url) 
 */
function ThumbFlow (owner, inputList)
{
 	/***** Settings  *******/
	this.thumbSpace = 30;			// Distance between thumbnails
	this.thumbScale = 0.7;			// Scaling of thumbnails not selected
	this.thumbImgTitleSpace = 10;	// Space between the thumbnails title and image (or magnifire, when thumbnail is selected)

	/***** Fields ********/	
	this.owner = owner;				// The BookmarkFlow object containing this thumbflow	
	this.items = [];				// Array of ThumbItem objects
	this.selectedIndex = 0;			// Index of the item being selected

	this.thumbWidth = 0;			// Both to be calculated at initialization (based on magnifire size)
	this.thumbHeight = 0;			

	/***** Public API's *****/
	
	// Updating position of items (= set new positions for each item by CSS styling, animation is handled by CSS)
	this.update = function ()
	{		
		for (i = 0; i < this.items.length; i++)		/* update each cover item */
			this.items[i].update();
	};	
	// Scroll menu items to the new position
	this.flowTo = function (newIndex)
	{	 
		newIndex = Math.max(newIndex, 0);
		newIndex = Math.min(newIndex, this.items.length - 1);
		this.selectedIndex = newIndex;
		this.update();
	};	
	// Scroll items with 'step' steps. Positive or Negative values decide direction.
	this.flow = function(step) {	 	
		this.flowTo(this.selectedIndex + step);
	};	
	// Show the flow 
	this.show = function() {
//		this.thumbFlowArea.style.WebkitTransitionDuration = this.owner.thumbShowSpeed + "s";
/*		this.thumbFlowArea.style.height = 2*this.thumbHeight + "px";*/
		this.thumbFlowArea.style.opacity = 1;		
	}
	// Hide the flow
	this.hide = function() {
//		this.thumbFlowArea.style.WebkitTransitionDuration =  this.owner.thumbShowSpeed/2 + "s";
/*		this.thumbFlowArea.style.height = "0px";*/
		this.thumbFlowArea.style.opacity = 0;
	}
	// Load url based on the selected thumbnail
	this.load = function() {
		if (this.items.length > 0)
		{
			location.href = this.items[this.selectedIndex].url;
		}
	}

	/***** Initialization **/
	
	/* Calculate thumbnail size according to the magnifire height */
	this.thumbWidth = this.owner.magnifireWidth - 2 * this.owner.magnifirePadding;
	this.thumbHeight = this.owner.magnifireHeight;
	
	
	/* Create thumb flowing area div, and add it to the owner's bookmarkArea. This will contain all the thumbnails of this flow object. */
	this.thumbFlowArea = document.createElement("div");
	if (this.thumbFlowArea)
	{
		this.thumbFlowArea.setAttribute("class", "thumbFlowArea");
		this.thumbFlowArea.style.height = 2*this.thumbHeight + "px";
		this.thumbFlowArea.style.top = this.owner.magnifirePosY + "px";
//		this.thumbFlowArea.style.WebkitTransitionDuration = this.owner.thumbShowSpeed + "s";
	}
	this.owner.bookmarkArea.appendChild(this.thumbFlowArea);

	/* Fill array of items based on input list content and add to DOM */	
	if (inputList != null)	{
		var child;	
		var index = 0;
		for (var i = 0; i < inputList.childNodes.length; i++)
			if (inputList.childNodes[i].nodeName == "LI")
			{
			 	var item = new ThumbItem(this, index, inputList.childNodes[i]);
				this.items.push(item);
				this.thumbFlowArea.appendChild(item.itemDiv);
				index++;
			}
	}
	else	// Add text stating that there are no thumbnails
	{
		var text = document.createElement("span");
		text.setAttribute("class", "thumbEmpty");
		text.style.left = this.owner.magnifirePosX + 20 + "px";
		text.style.top = this.owner.magnifireHeight/2 + "px";
		text.innerHTML = "EMPTY FOLDER";
		this.thumbFlowArea.appendChild(text);
	}

}  // end of ThumbFlow class


/* Implementation of the ThumbItem class
 * Used by the ThumbFlow class to create its elements.
 *
 * thumbFlowObj - the parent object (thumbnail row to which the item belongs)
 * ind - index of this item in the thumbnail row
 * sourceEl - html element from which the item is created (eg. 'LI' element with 3 span tags)
 */
function ThumbItem(thumbFlowObj, ind, sourceEl) {

	/***** Fields ********/	
	this.thumbFlow = thumbFlowObj;
	this.index = ind;
	this.url = "";			// is set at object initialization
	
	/***** Public API's *****/
	
  	// Update this items position, based on the selected index in the menu (owner)
	this.update = function() {		
		var offset = this.index - this.thumbFlow.selectedIndex;
		
		var scalenew = (offset == 0) ? 1 : this.thumbFlow.thumbScale;
		
		/* calculate X coordinate */		
		// Base position: center of magnifire
		var xposnew = this.thumbFlow.owner.magnifirePosX + this.thumbFlow.owner.magnifireWidth / 2;
		// Adjustment for left/right
		if (offset > 0)
			xposnew = xposnew + (this.thumbFlow.owner.magnifireWidth - this.thumbFlow.thumbWidth*scalenew)/2;
		else if (offset < 0)
			xposnew = xposnew - (this.thumbFlow.owner.magnifireWidth - this.thumbFlow.thumbWidth*scalenew)/2;
		// Consider offset
		xposnew = xposnew + (this.thumbFlow.thumbWidth * this.thumbFlow.thumbScale + this.thumbFlow.thumbSpace) * offset;
		// Round and center div				
		xposnew = Math.round(xposnew - (this.thumbFlow.thumbWidth)/2);		
	
		/* opacity */
		var opnew = 1;
		if (offset != 0)		// calculate opacity for items not selected
			opnew = Math.max(0, this.thumbFlow.owner.opacStartValue - ((Math.abs(offset)-1)* this.thumbFlow.owner.opacStepValue));

		/* Set new values */
		this.itemDiv.style.webkitTransform='translateX('+xposnew+'px) scale('+scalenew+')';
		this.itemDiv.style.opacity = opnew;
		
		/* Position of the title */
		var top = 0;
		if (offset != 0)			// title goes under the image
			top = this.thumbFlow.thumbHeight + this.thumbFlow.thumbImgTitleSpace;
		else						// title goes under the magnifire
			top = this.thumbFlow.owner.magnifireHeight - this.thumbFlow.owner.magnifirePadding + this.thumbFlow.thumbImgTitleSpace;
		this.title.style.top = top + "px";
	};
	
	/***** Initialization **/
			
	// Init: creating the main div, holding the thumbnail 
	this.itemDiv = document.createElement("div");
	if (this.itemDiv)
	{
		this.itemDiv.setAttribute("class", "thumbItem");
		this.itemDiv.style.width = this.thumbFlow.thumbWidth + "px";
		this.itemDiv.style.height = this.thumbFlow.thumbHeight + "px";
		this.itemDiv.style.top = this.thumbFlow.owner.magnifirePadding + "px";
//		this.itemDiv.style.WebkitTransitionDuration = this.thumbFlow.owner.thumbFlowSpeed+"s";
		
		/* Using the sourceEl element to create content of the thumbnail.
		 * It should have 3 span tags, for: title, image name, and link address
		 */
		
		var child;		
		var count = 0;
		for (var i = 0; i < sourceEl.childNodes.length; i++)
		{
			child = sourceEl.childNodes[i];
			if (child.nodeName == "SPAN") {
				switch(count)
				{
					case 0:
					 	// add title
					 	this.title = document.createElement("span");
					 	this.title.setAttribute("class", "thumbTitle");
					 	this.title.style.top = this.thumbFlow.thumbHeight + "px";
//					 	this.title.style.WebkitTransitionDuration = this.thumbFlow.owner.thumbFlowSpeed+"s";
					 	this.title.innerHTML = child.innerHTML;
					 	this.itemDiv.appendChild(this.title);
						break;
					case 1:
						// add image
						this.img = document.createElement("img");
						this.img.setAttribute("class", "thumbImage");						
						/*
						* Change utility that captures web page images
						*/
						//this.img.setAttribute( "src", "http://images.shrinktheweb.com/xino.php?stwembed=1&stwaccesskeyid=a2ba60dd936feb7&stwsize=sm&stwurl="+child.innerHTML);
						this.img.setAttribute( "src", "" + child.innerHTML);
						this.itemDiv.appendChild(this.img);
						break;
					case 2:
						this.url = child.innerHTML;
						break;
					default: 
				}
				count++;
			}	
		} // end of for
		
	} // thumnail created
	
} // end of ThumbItem class

