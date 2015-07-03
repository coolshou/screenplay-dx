case $1 in
	"init" )
		echo "==============zcip start===================="
		echo "Zcip requesting auto ip ..."
		;;
	
	"config")
		echo "zcip ip=" $ip ", interface=" $interface
		echo $ip ":" $interface > /tmp/get_autoip
		ifconfig $interface $ip
		echo "===============zcip end====================="
		;;
	
	*)
		echo "unknown"
		;;
esac
