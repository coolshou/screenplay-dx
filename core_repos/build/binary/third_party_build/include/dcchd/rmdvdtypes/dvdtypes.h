/*****************************************************************
*** Copyright (c) 2002 Sigma Designs Inc. All rights reserved. ***
*****************************************************************/

/**
  @file   dvdtypes.h
  @brief  external defines and structures shared by application and DVD navigator.

  @ingroup dvdcontrol
  @author Mathieu Lacage, Michael Ignaszewski
  @date   2002-01-22
*/

#ifndef __DVDNAV_H__
#define __DVDNAV_H__

#ifndef DVD_SECTOR_SIZE
#define DVD_SECTOR_SIZE ((RMuint16)2048)
#endif

/**
   Language Code. See Annex B.
   and ISO 3166
   automatically generated from 
   http://www-old.ics.uci.edu/pub/ietf/http/related/iso3166.txt
   and $CARIBBEAN/scripts/iso3166.pl
 */
typedef enum {
	RM_COUNTRY_INVALID = 0,
	RM_COUNTRY_AFGHANISTAN = ('A'<<8) + 'F',
	RM_COUNTRY_ALBANIA = ('A'<<8) + 'L',
	RM_COUNTRY_ALGERIA = ('D'<<8) + 'Z',
	RM_COUNTRY_AMERICAN_SAMOA = ('A'<<8) + 'S',
	RM_COUNTRY_ANDORRA = ('A'<<8) + 'D',
	RM_COUNTRY_ANGOLA = ('A'<<8) + 'O',
	RM_COUNTRY_ANGUILLA = ('A'<<8) + 'I',
	RM_COUNTRY_ANTARCTICA = ('A'<<8) + 'Q',
	RM_COUNTRY_ANTIGUA_AND_BARBUDA = ('A'<<8) + 'G',
	RM_COUNTRY_ARGENTINA = ('A'<<8) + 'R',
	RM_COUNTRY_ARMENIA = ('A'<<8) + 'M',
	RM_COUNTRY_ARUBA = ('A'<<8) + 'W',
	RM_COUNTRY_AUSTRALIA = ('A'<<8) + 'U',
	RM_COUNTRY_AUSTRIA = ('A'<<8) + 'T',
	RM_COUNTRY_AZERBAIJAN = ('A'<<8) + 'Z',
	RM_COUNTRY_BAHAMAS = ('B'<<8) + 'S',
	RM_COUNTRY_BAHRAIN = ('B'<<8) + 'H',
	RM_COUNTRY_BANGLADESH = ('B'<<8) + 'D',
	RM_COUNTRY_BARBADOS = ('B'<<8) + 'B',
	RM_COUNTRY_BELARUS = ('B'<<8) + 'Y',
	RM_COUNTRY_BELGIUM = ('B'<<8) + 'E',
	RM_COUNTRY_BELIZE = ('B'<<8) + 'Z',
	RM_COUNTRY_BENIN = ('B'<<8) + 'J',
	RM_COUNTRY_BERMUDA = ('B'<<8) + 'M',
	RM_COUNTRY_BHUTAN = ('B'<<8) + 'T',
	RM_COUNTRY_BOLIVIA = ('B'<<8) + 'O',
	RM_COUNTRY_BOSNIA_AND_HERZEGOWINA = ('B'<<8) + 'A',
	RM_COUNTRY_BOTSWANA = ('B'<<8) + 'W',
	RM_COUNTRY_BOUVET_ISLAND = ('B'<<8) + 'V',
	RM_COUNTRY_BRAZIL = ('B'<<8) + 'R',
	RM_COUNTRY_BRITISH_INDIAN_OCEAN_TERRITORY = ('I'<<8) + 'O',
	RM_COUNTRY_BRUNEI_DARUSSALAM = ('B'<<8) + 'N',
	RM_COUNTRY_BULGARIA = ('B'<<8) + 'G',
	RM_COUNTRY_BURKINA_FASO = ('B'<<8) + 'F',
	RM_COUNTRY_BURUNDI = ('B'<<8) + 'I',
	RM_COUNTRY_CAMBODIA = ('K'<<8) + 'H',
	RM_COUNTRY_CAMEROON = ('C'<<8) + 'M',
	RM_COUNTRY_CANADA = ('C'<<8) + 'A',
	RM_COUNTRY_CAPE_VERDE = ('C'<<8) + 'V',
	RM_COUNTRY_CAYMAN_ISLANDS = ('K'<<8) + 'Y',
	RM_COUNTRY_CENTRAL_AFRICAN_REPUBLIC = ('C'<<8) + 'F',
	RM_COUNTRY_CHAD = ('T'<<8) + 'D',
	RM_COUNTRY_CHILE = ('C'<<8) + 'L',
	RM_COUNTRY_CHINA = ('C'<<8) + 'N',
	RM_COUNTRY_CHRISTMAS_ISLAND = ('C'<<8) + 'X',
	RM_COUNTRY_COCOS_ISLANDS = ('C'<<8) + 'C',
	RM_COUNTRY_COLOMBIA = ('C'<<8) + 'O',
	RM_COUNTRY_COMOROS = ('K'<<8) + 'M',
	RM_COUNTRY_CONGO = ('C'<<8) + 'G',
	RM_COUNTRY_COOK_ISLANDS = ('C'<<8) + 'K',
	RM_COUNTRY_COSTA_RICA = ('C'<<8) + 'R',
	RM_COUNTRY_COTE_DIVOIRE = ('C'<<8) + 'I',
	RM_COUNTRY_CROATIA = ('H'<<8) + 'R',
	RM_COUNTRY_CUBA = ('C'<<8) + 'U',
	RM_COUNTRY_CYPRUS = ('C'<<8) + 'Y',
	RM_COUNTRY_CZECH_REPUBLIC = ('C'<<8) + 'Z',
	RM_COUNTRY_DENMARK = ('D'<<8) + 'K',
	RM_COUNTRY_DJIBOUTI = ('D'<<8) + 'J',
	RM_COUNTRY_DOMINICA = ('D'<<8) + 'M',
	RM_COUNTRY_DOMINICAN_REPUBLIC = ('D'<<8) + 'O',
	RM_COUNTRY_EAST_TIMOR = ('T'<<8) + 'P',
	RM_COUNTRY_ECUADOR = ('E'<<8) + 'C',
	RM_COUNTRY_EGYPT = ('E'<<8) + 'G',
	RM_COUNTRY_EL_SALVADOR = ('S'<<8) + 'V',
	RM_COUNTRY_EQUATORIAL_GUINEA = ('G'<<8) + 'Q',
	RM_COUNTRY_ERITREA = ('E'<<8) + 'R',
	RM_COUNTRY_ESTONIA = ('E'<<8) + 'E',
	RM_COUNTRY_ETHIOPIA = ('E'<<8) + 'T',
	RM_COUNTRY_FALKLAND_ISLANDS = ('F'<<8) + 'K',
	RM_COUNTRY_FAROE_ISLANDS = ('F'<<8) + 'O',
	RM_COUNTRY_FIJI = ('F'<<8) + 'J',
	RM_COUNTRY_FINLAND = ('F'<<8) + 'I',
	RM_COUNTRY_FRANCE = ('F'<<8) + 'R',
	RM_COUNTRY_FRANCE_METROPOLITAN = ('F'<<8) + 'X',
	RM_COUNTRY_FRENCH_GUIANA = ('G'<<8) + 'F',
	RM_COUNTRY_FRENCH_POLYNESIA = ('P'<<8) + 'F',
	RM_COUNTRY_FRENCH_SOUTHERN_TERRITORIES = ('T'<<8) + 'F',
	RM_COUNTRY_GABON = ('G'<<8) + 'A',
	RM_COUNTRY_GAMBIA = ('G'<<8) + 'M',
	RM_COUNTRY_GEORGIA = ('G'<<8) + 'E',
	RM_COUNTRY_GERMANY = ('D'<<8) + 'E',
	RM_COUNTRY_GHANA = ('G'<<8) + 'H',
	RM_COUNTRY_GIBRALTAR = ('G'<<8) + 'I',
	RM_COUNTRY_GREECE = ('G'<<8) + 'R',
	RM_COUNTRY_GREENLAND = ('G'<<8) + 'L',
	RM_COUNTRY_GRENADA = ('G'<<8) + 'D',
	RM_COUNTRY_GUADELOUPE = ('G'<<8) + 'P',
	RM_COUNTRY_GUAM = ('G'<<8) + 'U',
	RM_COUNTRY_GUATEMALA = ('G'<<8) + 'T',
	RM_COUNTRY_GUINEA = ('G'<<8) + 'N',
	RM_COUNTRY_GUINEA_BISSAU = ('G'<<8) + 'W',
	RM_COUNTRY_GUYANA = ('G'<<8) + 'Y',
	RM_COUNTRY_HAITI = ('H'<<8) + 'T',
	RM_COUNTRY_HEARD_AND_MC_DONALD_ISLANDS = ('H'<<8) + 'M',
	RM_COUNTRY_HONDURAS = ('H'<<8) + 'N',
	RM_COUNTRY_HONG_KONG = ('H'<<8) + 'K',
	RM_COUNTRY_HUNGARY = ('H'<<8) + 'U',
	RM_COUNTRY_ICELAND = ('I'<<8) + 'S',
	RM_COUNTRY_INDIA = ('I'<<8) + 'N',
	RM_COUNTRY_INDONESIA = ('I'<<8) + 'D',
	RM_COUNTRY_IRAN = ('I'<<8) + 'R',
	RM_COUNTRY_IRAQ = ('I'<<8) + 'Q',
	RM_COUNTRY_IRELAND = ('I'<<8) + 'E',
	RM_COUNTRY_ISRAEL = ('I'<<8) + 'L',
	RM_COUNTRY_ITALY = ('I'<<8) + 'T',
	RM_COUNTRY_JAMAICA = ('J'<<8) + 'M',
	RM_COUNTRY_JAPAN = ('J'<<8) + 'P',
	RM_COUNTRY_JORDAN = ('J'<<8) + 'O',
	RM_COUNTRY_KAZAKHSTAN = ('K'<<8) + 'Z',
	RM_COUNTRY_KENYA = ('K'<<8) + 'E',
	RM_COUNTRY_KIRIBATI = ('K'<<8) + 'I',
	RM_COUNTRY_KOREA_DEMOCRATIC_PEOPLES_REPUBLIC_OF = ('K'<<8) + 'P',
	RM_COUNTRY_KOREA_REPUBLIC_OF = ('K'<<8) + 'R',
	RM_COUNTRY_KUWAIT = ('K'<<8) + 'W',
	RM_COUNTRY_KYRGYZSTAN = ('K'<<8) + 'G',
	RM_COUNTRY_LAO_PEOPLES_DEMOCRATIC_REPUBLIC = ('L'<<8) + 'A',
	RM_COUNTRY_LATVIA = ('L'<<8) + 'V',
	RM_COUNTRY_LEBANON = ('L'<<8) + 'B',
	RM_COUNTRY_LESOTHO = ('L'<<8) + 'S',
	RM_COUNTRY_LIBERIA = ('L'<<8) + 'R',
	RM_COUNTRY_LIBYAN_ARAB_JAMAHIRIYA = ('L'<<8) + 'Y',
	RM_COUNTRY_LIECHTENSTEIN = ('L'<<8) + 'I',
	RM_COUNTRY_LITHUANIA = ('L'<<8) + 'T',
	RM_COUNTRY_LUXEMBOURG = ('L'<<8) + 'U',
	RM_COUNTRY_MACAU = ('M'<<8) + 'O',
	RM_COUNTRY_MACEDONIA_THE_FORMER_YUGOSLAV_REPUBLIC_OF = ('M'<<8) + 'K',
	RM_COUNTRY_MADAGASCAR = ('M'<<8) + 'G',
	RM_COUNTRY_MALAWI = ('M'<<8) + 'W',
	RM_COUNTRY_MALAYSIA = ('M'<<8) + 'Y',
	RM_COUNTRY_MALDIVES = ('M'<<8) + 'V',
	RM_COUNTRY_MALI = ('M'<<8) + 'L',
	RM_COUNTRY_MALTA = ('M'<<8) + 'T',
	RM_COUNTRY_MARSHALL_ISLANDS = ('M'<<8) + 'H',
	RM_COUNTRY_MARTINIQUE = ('M'<<8) + 'Q',
	RM_COUNTRY_MAURITANIA = ('M'<<8) + 'R',
	RM_COUNTRY_MAURITIUS = ('M'<<8) + 'U',
	RM_COUNTRY_MAYOTTE = ('Y'<<8) + 'T',
	RM_COUNTRY_MEXICO = ('M'<<8) + 'X',
	RM_COUNTRY_MICRONESIA_FEDERATED_STATES_OF = ('F'<<8) + 'M',
	RM_COUNTRY_MOLDOVA_REPUBLIC_OF = ('M'<<8) + 'D',
	RM_COUNTRY_MONACO = ('M'<<8) + 'C',
	RM_COUNTRY_MONGOLIA = ('M'<<8) + 'N',
	RM_COUNTRY_MONTSERRAT = ('M'<<8) + 'S',
	RM_COUNTRY_MOROCCO = ('M'<<8) + 'A',
	RM_COUNTRY_MOZAMBIQUE = ('M'<<8) + 'Z',
	RM_COUNTRY_MYANMAR = ('M'<<8) + 'M',
	RM_COUNTRY_NAMIBIA = ('N'<<8) + 'A',
	RM_COUNTRY_NAURU = ('N'<<8) + 'R',
	RM_COUNTRY_NEPAL = ('N'<<8) + 'P',
	RM_COUNTRY_NETHERLANDS = ('N'<<8) + 'L',
	RM_COUNTRY_NETHERLANDS_ANTILLES = ('A'<<8) + 'N',
	RM_COUNTRY_NEW_CALEDONIA = ('N'<<8) + 'C',
	RM_COUNTRY_NEW_ZEALAND = ('N'<<8) + 'Z',
	RM_COUNTRY_NICARAGUA = ('N'<<8) + 'I',
	RM_COUNTRY_NIGER = ('N'<<8) + 'E',
	RM_COUNTRY_NIGERIA = ('N'<<8) + 'G',
	RM_COUNTRY_NIUE = ('N'<<8) + 'U',
	RM_COUNTRY_NORFOLK_ISLAND = ('N'<<8) + 'F',
	RM_COUNTRY_NORTHERN_MARIANA_ISLANDS = ('M'<<8) + 'P',
	RM_COUNTRY_NORWAY = ('N'<<8) + 'O',
	RM_COUNTRY_OMAN = ('O'<<8) + 'M',
	RM_COUNTRY_PAKISTAN = ('P'<<8) + 'K',
	RM_COUNTRY_PALAU = ('P'<<8) + 'W',
	RM_COUNTRY_PANAMA = ('P'<<8) + 'A',
	RM_COUNTRY_PAPUA_NEW_GUINEA = ('P'<<8) + 'G',
	RM_COUNTRY_PARAGUAY = ('P'<<8) + 'Y',
	RM_COUNTRY_PERU = ('P'<<8) + 'E',
	RM_COUNTRY_PHILIPPINES = ('P'<<8) + 'H',
	RM_COUNTRY_PITCAIRN = ('P'<<8) + 'N',
	RM_COUNTRY_POLAND = ('P'<<8) + 'L',
	RM_COUNTRY_PORTUGAL = ('P'<<8) + 'T',
	RM_COUNTRY_PUERTO_RICO = ('P'<<8) + 'R',
	RM_COUNTRY_QATAR = ('Q'<<8) + 'A',
	RM_COUNTRY_REUNION = ('R'<<8) + 'E',
	RM_COUNTRY_ROMANIA = ('R'<<8) + 'O',
	RM_COUNTRY_RUSSIAN_FEDERATION = ('R'<<8) + 'U',
	RM_COUNTRY_RWANDA = ('R'<<8) + 'W',
	RM_COUNTRY_SAINT_KITTS_AND_NEVIS = ('K'<<8) + 'N',
	RM_COUNTRY_SAINT_LUCIA = ('L'<<8) + 'C',
	RM_COUNTRY_SAINT_VINCENT_AND_THE_GRENADINES = ('V'<<8) + 'C',
	RM_COUNTRY_SAMOA = ('W'<<8) + 'S',
	RM_COUNTRY_SAN_MARINO = ('S'<<8) + 'M',
	RM_COUNTRY_SAO_TOME_AND_PRINCIPE = ('S'<<8) + 'T',
	RM_COUNTRY_SAUDI_ARABIA = ('S'<<8) + 'A',
	RM_COUNTRY_SENEGAL = ('S'<<8) + 'N',
	RM_COUNTRY_SEYCHELLES = ('S'<<8) + 'C',
	RM_COUNTRY_SIERRA_LEONE = ('S'<<8) + 'L',
	RM_COUNTRY_SINGAPORE = ('S'<<8) + 'G',
	RM_COUNTRY_SLOVAKIA = ('S'<<8) + 'K',
	RM_COUNTRY_SLOVENIA = ('S'<<8) + 'I',
	RM_COUNTRY_SOLOMON_ISLANDS = ('S'<<8) + 'B',
	RM_COUNTRY_SOMALIA = ('S'<<8) + 'O',
	RM_COUNTRY_SOUTH_AFRICA = ('Z'<<8) + 'A',
	RM_COUNTRY_SPAIN = ('E'<<8) + 'S',
	RM_COUNTRY_SRI_LANKA = ('L'<<8) + 'K',
	RM_COUNTRY_ST_HELENA = ('S'<<8) + 'H',
	RM_COUNTRY_ST_PIERRE_AND_MIQUELON = ('P'<<8) + 'M',
	RM_COUNTRY_SUDAN = ('S'<<8) + 'D',
	RM_COUNTRY_SURINAME = ('S'<<8) + 'R',
	RM_COUNTRY_SVALBARD_AND_JAN_MAYEN_ISLANDS = ('S'<<8) + 'J',
	RM_COUNTRY_SWAZILAND = ('S'<<8) + 'Z',
	RM_COUNTRY_SWEDEN = ('S'<<8) + 'E',
	RM_COUNTRY_SWITZERLAND = ('C'<<8) + 'H',
	RM_COUNTRY_SYRIAN_ARAB_REPUBLIC = ('S'<<8) + 'Y',
	RM_COUNTRY_TAIWAN_PROVINCE_OF_CHINA = ('T'<<8) + 'W',
	RM_COUNTRY_TAJIKISTAN = ('T'<<8) + 'J',
	RM_COUNTRY_TANZANIA_UNITED_REPUBLIC_OF = ('T'<<8) + 'Z',
	RM_COUNTRY_THAILAND = ('T'<<8) + 'H',
	RM_COUNTRY_TOGO = ('T'<<8) + 'G',
	RM_COUNTRY_TOKELAU = ('T'<<8) + 'K',
	RM_COUNTRY_TONGA = ('T'<<8) + 'O',
	RM_COUNTRY_TRINIDAD_AND_TOBAGO = ('T'<<8) + 'T',
	RM_COUNTRY_TUNISIA = ('T'<<8) + 'N',
	RM_COUNTRY_TURKEY = ('T'<<8) + 'R',
	RM_COUNTRY_TURKMENISTAN = ('T'<<8) + 'M',
	RM_COUNTRY_TURKS_AND_CAICOS_ISLANDS = ('T'<<8) + 'C',
	RM_COUNTRY_TUVALU = ('T'<<8) + 'V',
	RM_COUNTRY_UGANDA = ('U'<<8) + 'G',
	RM_COUNTRY_UKRAINE = ('U'<<8) + 'A',
	RM_COUNTRY_UNITED_ARAB_EMIRATES = ('A'<<8) + 'E',
	RM_COUNTRY_UNITED_KINGDOM = ('G'<<8) + 'B',
	RM_COUNTRY_UNITED_STATES = ('U'<<8) + 'S',
	RM_COUNTRY_UNITED_STATES_MINOR_OUTLYING_ISLANDS = ('U'<<8) + 'M',
	RM_COUNTRY_URUGUAY = ('U'<<8) + 'Y',
	RM_COUNTRY_UZBEKISTAN = ('U'<<8) + 'Z',
	RM_COUNTRY_VANUATU = ('V'<<8) + 'U',
	RM_COUNTRY_VATICAN_CITY_STATE = ('V'<<8) + 'A',
	RM_COUNTRY_VENEZUELA = ('V'<<8) + 'E',
	RM_COUNTRY_VIET_NAM = ('V'<<8) + 'N',
	RM_COUNTRY_VIRGIN_ISLANDS_BRITISH = ('V'<<8) + 'G',
	RM_COUNTRY_VIRGIN_ISLANDS_US = ('V'<<8) + 'I',
	RM_COUNTRY_WALLIS_AND_FUTUNA_ISLANDS = ('W'<<8) + 'F',
	RM_COUNTRY_WESTERN_SAHARA = ('E'<<8) + 'H',
	RM_COUNTRY_YEMEN = ('Y'<<8) + 'E',
	RM_COUNTRY_YUGOSLAVIA = ('Y'<<8) + 'U',
	RM_COUNTRY_ZAIRE = ('Z'<<8) + 'R',
	RM_COUNTRY_ZAMBIA = ('Z'<<8) + 'M',
	RM_COUNTRY_ZIMBABWE = ('Z'<<8) + 'W',
	RM_COUNTRY_NOT_SPECIFIED = 0xffff
} RMdvdCountryCode;


/** 
    ISO 639
    automatically generated from:
    http://www.oasis-open.org/cover/iso639a.html 
    and $CARIBBEAN/scripts/iso639.pl
 */
typedef enum {
	RM_LANGUAGE_INVALID = 0,
	RM_LANGUAGE_AFAR  = ('a'<<8) + 'a',
	RM_LANGUAGE_ABKHAZIAN  = ('a'<<8) + 'b',
	RM_LANGUAGE_AFRIKAANS  = ('a'<<8) + 'f',
	RM_LANGUAGE_AMHARIC  = ('a'<<8) + 'm',
	RM_LANGUAGE_ARABIC  = ('a'<<8) + 'r',
	RM_LANGUAGE_ASSAMESE  = ('a'<<8) + 's',
	RM_LANGUAGE_AYMARA  = ('a'<<8) + 'y',
	RM_LANGUAGE_AZERBAIJANI  = ('a'<<8) + 'z',
	RM_LANGUAGE_BASHKIR  = ('b'<<8) + 'a',
	RM_LANGUAGE_BYELORUSSIAN  = ('b'<<8) + 'e',
	RM_LANGUAGE_BULGARIAN  = ('b'<<8) + 'g',
	RM_LANGUAGE_BIHARI  = ('b'<<8) + 'h',
	RM_LANGUAGE_BISLAMA  = ('b'<<8) + 'i',
	RM_LANGUAGE_BENGALI = ('b'<<8) + 'n',
	RM_LANGUAGE_TIBETAN  = ('b'<<8) + 'o',
	RM_LANGUAGE_BRETON  = ('b'<<8) + 'r',
	RM_LANGUAGE_CATALAN  = ('c'<<8) + 'a',
	RM_LANGUAGE_CORSICAN  = ('c'<<8) + 'o',
	RM_LANGUAGE_CZECH  = ('c'<<8) + 's',
	RM_LANGUAGE_WELSH  = ('c'<<8) + 'y',
	RM_LANGUAGE_DANISH  = ('d'<<8) + 'a',
	RM_LANGUAGE_GERMAN  = ('d'<<8) + 'e',
	RM_LANGUAGE_BHUTANI  = ('d'<<8) + 'z',
	RM_LANGUAGE_GREEK  = ('e'<<8) + 'l',
	RM_LANGUAGE_ENGLISH  = ('e'<<8) + 'n',
	RM_LANGUAGE_ESPERANTO  = ('e'<<8) + 'o',
	RM_LANGUAGE_SPANISH  = ('e'<<8) + 's',
	RM_LANGUAGE_ESTONIAN  = ('e'<<8) + 't',
	RM_LANGUAGE_BASQUE  = ('e'<<8) + 'u',
	RM_LANGUAGE_PERSIAN  = ('f'<<8) + 'a',
	RM_LANGUAGE_FINNISH  = ('f'<<8) + 'i',
	RM_LANGUAGE_FIJI  = ('f'<<8) + 'j',
	RM_LANGUAGE_FAROESE  = ('f'<<8) + 'o',
	RM_LANGUAGE_FRENCH  = ('f'<<8) + 'r',
	RM_LANGUAGE_FRISIAN  = ('f'<<8) + 'y',
	RM_LANGUAGE_IRISH  = ('g'<<8) + 'a',
	RM_LANGUAGE_SCOTS  = ('g'<<8) + 'd',
	RM_LANGUAGE_GALICIAN  = ('g'<<8) + 'l',
	RM_LANGUAGE_GUARANI  = ('g'<<8) + 'n',
	RM_LANGUAGE_GUJARATI  = ('g'<<8) + 'u',
	RM_LANGUAGE_HAUSA  = ('h'<<8) + 'a',
	RM_LANGUAGE_HEBREW  = ('h'<<8) + 'e',
	RM_LANGUAGE_HINDI  = ('h'<<8) + 'i',
	RM_LANGUAGE_CROATIAN  = ('h'<<8) + 'r',
	RM_LANGUAGE_HUNGARIAN  = ('h'<<8) + 'u',
	RM_LANGUAGE_ARMENIAN  = ('h'<<8) + 'y',
	RM_LANGUAGE_INTERLINGUA  = ('i'<<8) + 'a',
	RM_LANGUAGE_INTERLINGUE  = ('i'<<8) + 'e',
	RM_LANGUAGE_INUPIAK  = ('i'<<8) + 'k',
	RM_LANGUAGE_INDONESIAN  = ('i'<<8) + 'd',
	RM_LANGUAGE_ICELANDIC  = ('i'<<8) + 's',
	RM_LANGUAGE_ITALIAN  = ('i'<<8) + 't',
	RM_LANGUAGE_INUKTITUT  = ('i'<<8) + 'u',
	RM_LANGUAGE_JAPANESE  = ('j'<<8) + 'a',
	RM_LANGUAGE_JAVANESE  = ('j'<<8) + 'v',
	RM_LANGUAGE_GEORGIAN  = ('k'<<8) + 'a',
	RM_LANGUAGE_KAZAKH  = ('k'<<8) + 'k',
	RM_LANGUAGE_GREENLANDIC  = ('k'<<8) + 'l',
	RM_LANGUAGE_CAMBODIAN  = ('k'<<8) + 'm',
	RM_LANGUAGE_KANNADA  = ('k'<<8) + 'n',
	RM_LANGUAGE_KOREAN  = ('k'<<8) + 'o',
	RM_LANGUAGE_KASHMIRI  = ('k'<<8) + 's',
	RM_LANGUAGE_KURDISH  = ('k'<<8) + 'u',
	RM_LANGUAGE_KIRGHIZ  = ('k'<<8) + 'y',
	RM_LANGUAGE_LATIN  = ('l'<<8) + 'a',
	RM_LANGUAGE_LINGALA  = ('l'<<8) + 'n',
	RM_LANGUAGE_LAOTHIAN  = ('l'<<8) + 'o',
	RM_LANGUAGE_LITHUANIAN  = ('l'<<8) + 't',
	RM_LANGUAGE_LATVIAN = ('l'<<8) + 'v',
	RM_LANGUAGE_MALAGASY  = ('m'<<8) + 'g',
	RM_LANGUAGE_MAORI  = ('m'<<8) + 'i',
	RM_LANGUAGE_MACEDONIAN  = ('m'<<8) + 'k',
	RM_LANGUAGE_MALAYALAM  = ('m'<<8) + 'l',
	RM_LANGUAGE_MONGOLIAN  = ('m'<<8) + 'n',
	RM_LANGUAGE_MOLDAVIAN  = ('m'<<8) + 'o',
	RM_LANGUAGE_MARATHI  = ('m'<<8) + 'r',
	RM_LANGUAGE_MALAY  = ('m'<<8) + 's',
	RM_LANGUAGE_MALTESE  = ('m'<<8) + 't',
	RM_LANGUAGE_BURMESE  = ('m'<<8) + 'y',
	RM_LANGUAGE_NAURU  = ('n'<<8) + 'a',
	RM_LANGUAGE_NEPALI  = ('n'<<8) + 'e',
	RM_LANGUAGE_DUTCH  = ('n'<<8) + 'l',
	RM_LANGUAGE_NORWEGIAN  = ('n'<<8) + 'o',
	RM_LANGUAGE_OCCITAN  = ('o'<<8) + 'c',
	RM_LANGUAGE_AFAN  = ('o'<<8) + 'm',
	RM_LANGUAGE_ORIYA  = ('o'<<8) + 'r',
	RM_LANGUAGE_PUNJABI  = ('p'<<8) + 'a',
	RM_LANGUAGE_POLISH  = ('p'<<8) + 'l',
	RM_LANGUAGE_PASHTO = ('p'<<8) + 's',
	RM_LANGUAGE_PORTUGUESE  = ('p'<<8) + 't',
	RM_LANGUAGE_QUECHUA  = ('q'<<8) + 'u',
	RM_LANGUAGE_RHAETO_ROMANCE  = ('r'<<8) + 'm',
	RM_LANGUAGE_KURUNDI  = ('r'<<8) + 'n',
	RM_LANGUAGE_ROMANIAN  = ('r'<<8) + 'o',
	RM_LANGUAGE_RUSSIAN  = ('r'<<8) + 'u',
	RM_LANGUAGE_KINYARWANDA  = ('r'<<8) + 'w',
	RM_LANGUAGE_SANSKRIT  = ('s'<<8) + 'a',
	RM_LANGUAGE_SINDHI  = ('s'<<8) + 'd',
	RM_LANGUAGE_SANGHO  = ('s'<<8) + 'g',
	RM_LANGUAGE_SERBO_CROATIAN  = ('s'<<8) + 'h',
	RM_LANGUAGE_SINGHALESE  = ('s'<<8) + 'i',
	RM_LANGUAGE_SLOVAK  = ('s'<<8) + 'k',
	RM_LANGUAGE_SLOVENIAN  = ('s'<<8) + 'l',
	RM_LANGUAGE_SAMOAN  = ('s'<<8) + 'm',
	RM_LANGUAGE_SHONA  = ('s'<<8) + 'n',
	RM_LANGUAGE_SOMALI  = ('s'<<8) + 'o',
	RM_LANGUAGE_ALBANIAN  = ('s'<<8) + 'q',
	RM_LANGUAGE_SERBIAN  = ('s'<<8) + 'r',
	RM_LANGUAGE_SISWATI  = ('s'<<8) + 's',
	RM_LANGUAGE_SESOTHO  = ('s'<<8) + 't',
	RM_LANGUAGE_SUNDANESE  = ('s'<<8) + 'u',
	RM_LANGUAGE_SWEDISH  = ('s'<<8) + 'v',
	RM_LANGUAGE_SWAHILI  = ('s'<<8) + 'w',
	RM_LANGUAGE_TAMIL  = ('t'<<8) + 'a',
	RM_LANGUAGE_TELUGU  = ('t'<<8) + 'e',
	RM_LANGUAGE_TAJIK  = ('t'<<8) + 'g',
	RM_LANGUAGE_THAI  = ('t'<<8) + 'h',
	RM_LANGUAGE_TIGRINYA  = ('t'<<8) + 'i',
	RM_LANGUAGE_TURKMEN  = ('t'<<8) + 'k',
	RM_LANGUAGE_TAGALOG  = ('t'<<8) + 'l',
	RM_LANGUAGE_SETSWANA  = ('t'<<8) + 'n',
	RM_LANGUAGE_TONGA  = ('t'<<8) + 'o',
	RM_LANGUAGE_TURKISH  = ('t'<<8) + 'r',
	RM_LANGUAGE_TSONGA  = ('t'<<8) + 's',
	RM_LANGUAGE_TATAR  = ('t'<<8) + 't',
	RM_LANGUAGE_TWI  = ('t'<<8) + 'w',
	RM_LANGUAGE_UIGUR  = ('u'<<8) + 'g',
	RM_LANGUAGE_UKRAINIAN  = ('u'<<8) + 'k',
	RM_LANGUAGE_URDU  = ('u'<<8) + 'r',
	RM_LANGUAGE_UZBEK  = ('u'<<8) + 'z',
	RM_LANGUAGE_VIETNAMESE  = ('v'<<8) + 'i',
	RM_LANGUAGE_VOLAPUK  = ('v'<<8) + 'o',
	RM_LANGUAGE_WOLOF  = ('w'<<8) + 'o',
	RM_LANGUAGE_XHOSA  = ('x'<<8) + 'h',
	RM_LANGUAGE_YIDDISH  = ('y'<<8) + 'i',
	RM_LANGUAGE_YORUBA  = ('y'<<8) + 'o',
	RM_LANGUAGE_ZHUANG  = ('z'<<8) + 'a',
	RM_LANGUAGE_CHINESE  = ('z'<<8) + 'h',
	RM_LANGUAGE_ZULU  = ('z'<<8) + 'u',

	RM_LANGUAGE_HEBREW_OLD = ('i'<<8) + 'w',
	RM_LANGUAGE_INDONESIAN_OLD = ('i'<<8) + 'n',
	RM_LANGUAGE_YIDDISH_OLD = ('j'<<8) + 'i',
	RM_LANGUAGE_JAVANESE_OLD = ('j'<<8) + 'w',
} RMdvdLanguageCode;

#define BOOKMARK_SIZE 1024

/**********************************************************
 * Enums.
 **********************************************************/

/**
   Menu Ids. 
 */
typedef enum {
/** Title menu ID */
	RM_DVD_MENU_ID_TITLE      = 0x02,
/** Root menu ID */
	RM_DVD_MENU_ID_ROOT       = 0x03,
/** Subpicture menu ID */
	RM_DVD_MENU_ID_SUBPICTURE = 0x04,
/** Audio menu ID */
	RM_DVD_MENU_ID_AUDIO      = 0x05,
/** Angle menu ID */
	RM_DVD_MENU_ID_ANGLE      = 0x06,
/** Chapter menu ID */
	RM_DVD_MENU_ID_PTT        = 0x07
} RMdvdMenuId;

/**
   Menu Existence flags
 */
typedef enum {
/** Title menu */
	RM_DVD_TITLE_MENU_EXIST = 1 << RM_DVD_MENU_ID_TITLE,
/** Root menu */
	RM_DVD_ROOT_MENU_EXIST = 1 << RM_DVD_MENU_ID_ROOT,
/** Subpicture menu */
	RM_DVD_SUBPICTURE_MENU_EXIST = 1 << RM_DVD_MENU_ID_SUBPICTURE,
/** Audio menu */
	RM_DVD_AUDIO_MENU_EXIST = 1 << RM_DVD_MENU_ID_AUDIO,
/** Angle menu */
	RM_DVD_ANGLE_MENU_EXIST = 1 << RM_DVD_MENU_ID_ANGLE,
/** Chapter menu */
	RM_DVD_PTT_MENU_EXIST = 1 << RM_DVD_MENU_ID_PTT
} RMdvdMenuExistence;

/**
   Parental levels.
 */
typedef enum {
/** Parental level 1*/
	RM_DVD_PARENTAL_LEVEL_1         =  1,
/** Parental level 2*/
	RM_DVD_PARENTAL_LEVEL_2         =  2,
/** Parental level 3*/
	RM_DVD_PARENTAL_LEVEL_3         =  3,
/** Parental level 4*/
	RM_DVD_PARENTAL_LEVEL_4         =  4,
/** Parental level 5*/
	RM_DVD_PARENTAL_LEVEL_5         =  5,
/** Parental level 6*/
	RM_DVD_PARENTAL_LEVEL_6         =  6,
/** Parental level 7*/
	RM_DVD_PARENTAL_LEVEL_7         =  7,
/** Parental level 8*/
	RM_DVD_PARENTAL_LEVEL_8         =  8,
/** Parental level disabled*/
	RM_DVD_PARENTAL_LEVEL_DISABLED  = 0xf
} RMdvdParentalLevel;


/** Scan type */
typedef enum {
	/** Resume normal playback. */
	RM_DVD_SCAN_NO_SCAN,
	/** Play forward with all frames. */
	RM_DVD_SCAN_FORWARD_ALL_FRAMES,
	/** Play forward with only I frames. */
	RM_DVD_SCAN_FORWARD_I_FRAMES,
	/** Play backward with all frames. */
	RM_DVD_SCAN_BACKWARD_ALL_FRAMES,
	/** Play backward with only I frames. */
	RM_DVD_SCAN_BACKWARD_I_FRAMES
} RMdvdScanType;


/** Display and aspect ratio modes */
typedef enum {
	/** 4:3 source, 4:3 output display*/
	RM_DVD_VIDEO_4_3__4_3_RECT = 1,
	/** 4:3 source, 16:9 output display, crop top and bottom*/
	RM_DVD_VIDEO_4_3__16_9_ZOOM_ON,
	/** 4:3 source, 16:9 output display, black band on sides*/
	RM_DVD_VIDEO_4_3__16_9_ZOOM_OFF,
	/** 16:9 source, 16:9 output display. This is the so-called 'Wide' mode.*/
	RM_DVD_VIDEO_16_9__16_9_RECT,
	/** 16:9 source, pan and scan, 4:3 output display*/
	RM_DVD_VIDEO_16_9__4_3_PANSCAN,
	/** 16:9 source, letter box, 4:3 output display*/
	RM_DVD_VIDEO_16_9__4_3_LETTERBOX
} RMdvdVideoMode;

/**
	Audio types.
*/
typedef enum {
	/** AC3 Audio*/
	RM_DVD_AUDIO_AC3,
	/** MPEG Audio*/
	RM_DVD_AUDIO_MPEG,
	/** PCM Audio for AOB*/
	RM_DVD_AUDIO_PCM_AOB,
	/** PCM Audio for VOB*/
	RM_DVD_AUDIO_PCM_VOB,
	/** PCM Audio */
	RM_DVD_AUDIO_PCM,
	/** REVERSE PCM Audio */
	RM_DVD_AUDIO_RPCM,
	/** DTS Audio*/
	RM_DVD_AUDIO_DTS,
	/** SDDS Audio*/
	RM_DVD_AUDIO_SDDS,
	/** Mpeg2 extension bitstream. */
	RM_DVD_AUDIO_MPEG_EXTENSION,
	/** MLP audio */
	RM_DVD_AUDIO_MLP,	
} RMdvdAudioType;

/**
   audio capabilities. see SPRM(15), VI4-172.
 */
typedef enum {
	RM_DVD_CAN_SDDS_KARAOKE = 1<<2,
	RM_DVD_CAN_DTS_KARAOKE = 1<<3,
	RM_DVD_CAN_MPEG_KARAOKE = 1<<4,
	RM_DVD_CAN_AC3_KARAOKE = 1<<6,
	RM_DVD_CAN_PCM_KARAOKE = 1<<7,
	RM_DVD_CAN_SDDS = 1<<10,
	RM_DVD_CAN_DTS = 1<<11,
	RM_DVD_CAN_MPEG = 1<<12,
	RM_DVD_CAN_AC3 = 1<<14
} RMdvdAudioCapability;

/** see Annex C. */
typedef enum {
	RM_DVD_AUDIO_NOT_SPECIFIED = 0,
	RM_DVD_AUDIO_KARAOKE = 1,
	RM_DVD_AUDIO_SURROUND = 2
} RMdvdAudioApplicationMode;

typedef enum {
	RM_DVD_AUDIO_16_BITS = 0,
	RM_DVD_AUDIO_20_BITS = 1,
	RM_DVD_AUDIO_24_BITS = 2
} RMdvdAudioQuantization;

/** see AST_ATR as referenced in RMdvdAudioStream */
typedef enum {
	/** 48kHz frequency */
	RM_DVD_AUDIO_48KHz = 0,
	/** 96kHz frequency */
	RM_DVD_AUDIO_96KHz = 1
} RMdvdAudioFrequency;

/** see AST_ATR as referenced in RMdvdAudioStream */
typedef enum {
	/** The stream has 1 channel*/
	RM_DVD_AUDIO_CHANNELS_1 = 0,
	/** The stream has 2 channels*/
	RM_DVD_AUDIO_CHANNELS_2 = 1,
	/** The stream has 3 channels*/
	RM_DVD_AUDIO_CHANNELS_3 = 2,
	/** The stream has 4 channels*/
	RM_DVD_AUDIO_CHANNELS_4 = 3,
	/** The stream has 5 channels*/
	RM_DVD_AUDIO_CHANNELS_5 = 4,
	/** The stream has 6 channels*/
	RM_DVD_AUDIO_CHANNELS_6 = 5,
	/** The stream has 7 channels*/
	RM_DVD_AUDIO_CHANNELS_7 = 6,
	/** The stream has 8 channels*/
	RM_DVD_AUDIO_CHANNELS_8 = 7,
} RMdvdAudioChannels;

/** see VI4-28, CHRS */
typedef enum {
	RM_DVD_CHARSET_UNICODE = 0x0,
	RM_DVD_CHARSET_ISO646 = 0x1, /* 7 bit ascii */
	RM_DVD_CHARSET_JIS = 0x10, /* JIS Roman & JIS Kanji 1990. see Annex A.4 */
	RM_DVD_CHARSET_ISO8859 = 0x11, /* 8 bit ascii */
	RM_DVD_CHARSET_SHIFT_JIS = 0x12 /* Shift JIS Kanji including JIS Roman & JIS Katakana */
} RMdvdCharset;

/** DVD Domain type */
typedef enum {
	RM_DVD_DOMAIN_FPPGC,
	RM_DVD_DOMAIN_VMGM,
	RM_DVD_DOMAIN_VTSM,
	RM_DVD_DOMAIN_VTSTT
} RMdvdDomainType;

/** Simple Region code aliases */
#define RM_DVD_REGION_NORTH_AMERICA            RM_DVD_REGION_1
#define RM_DVD_REGION_WESTERN_EUROPE_JAPAN     RM_DVD_REGION_2
#define RM_DVD_REGION_SOUTHEAST_ASIA           RM_DVD_REGION_3
#define RM_DVD_REGION_SOUTH_AMERICA_AUSTRALIA  RM_DVD_REGION_4
#define RM_DVD_REGION_EASTERN_EUROPE_AFRICA    RM_DVD_REGION_5
#define RM_DVD_REGION_CHINA                    RM_DVD_REGION_6
#define RM_DVD_REGION_FREE                     RM_DVD_REGION_0

/** DVD Region codes */
typedef enum {
	RM_DVD_REGION_1 = 1<<0,
	RM_DVD_REGION_2 = 1<<1,
	RM_DVD_REGION_3 = 1<<2,
	RM_DVD_REGION_4 = 1<<3,
	RM_DVD_REGION_5 = 1<<4,
	RM_DVD_REGION_6 = 1<<5,
	RM_DVD_REGION_0 = 1<<6
} RMdvdRegionCode;

/*******************************************************************************
 * DVD Query structures
 *******************************************************************************/

/** Maximum number of audio streams. 0..7 */
#define MAX_AST 8		// 0..7
/** Maximum number of subpicture streams. 0..31 */
#define MAX_SPST 32		// 0..31
/** Maximum number of buttons. 1..36 */
#define MAX_BTN 36
/** Maximum number of titles 1..99 */
#define MAX_TT 99		// 1..99
/** Maximum number of angles. 1..9 */
#define MAX_AGL 9		// 1..9

/** 
	Title Search Pointer Table Information  : TT_SRPTI (Deprecated!!! Use RMdvdTitleInfo instead)
	see VI4-12
*/
typedef struct {
	/** Number of Titles (1-99) */
	RMuint8 numberOfTitles;
	/** Number of Angles (1-9) for each title */
	RMuint8 numberOfAnglesForTitle [MAX_TT];
	/** Number of Part_of_Titles (1-99) for each title */
	RMuint8 numberOfPTTsForTitle [MAX_TT];
} RMdvdTitleSRPTI;

/** 
    Each pointer in this structure is a string encoded in charset
    and ended with the charset-specified end-of-string character.
*/
typedef struct {
	RMdvdCharset charset;
	RMuint8 *titleName;
	RMuint8 *subTitleName;
	RMuint8 *orgTitleName;
	RMuint8 *producerName;
	RMuint8 *directorName;
	RMuint8 *scenarioWriter;
	RMuint8 *originalWriter;
	RMuint8 *actorsName[10]; /* max = 10. Too bad for the others. */
} RMdvdTitleTXTDT;

/** attributes of the Video Stream
    See VI4-7, VMGM_V_ATR,
        VI4-42, VTSM_V_ATR and
        VI4-46, VTS_V_ATR
*/
typedef struct {
	RMbool isMpeg2;
	RMbool isPAL;
	RMbool is16by9;
	RMbool isLetterboxOK;
	RMbool isPanScanOK;
	RMuint32 width;
	RMuint32 height;
	RMbool isSourceLetterboxed;
	RMbool isFilmCameraMode;
	RMbool isLine21Field1Recorded;
	RMbool isLine21Field2Recorded;
} RMdvdVideoStream;

/** attributes of the Audio Streams currently available.
    See VI4-9, VMGM_AST_ATR,
        VI4-44, VTSM_AST_ATR and
        VI4-49, VTS_AST_ATR
*/
typedef struct {
	RMdvdAudioType audioType;
	RMdvdAudioFrequency frequency;
	RMdvdAudioChannels numberOfChannels;
	RMbool isLanguage;
	RMdvdLanguageCode languageCode;
	RMuint8 languageCodeExtension;
	RMdvdAudioApplicationMode mode;
	RMdvdAudioQuantization quantization;
} RMdvdAudioStream;

/** attributes of the Audio Streams currently available.
*/
typedef struct {
	RMbool isAvailable[MAX_AST];
	RMdvdAudioStream audioStreams[MAX_AST];
} RMdvdAudioStreams;

/**
   attributes of the Sub Picture Streams currently available.
   See VI4-11 VMGM_SPST_ATR,
       VI4-46 VTSM_SPST_ATR and
       VI4-53, VTS_SPST_ATR
 */
typedef struct {
	RMbool isLanguage;
	RMdvdLanguageCode languageCode;
	RMuint8 languageCodeExtension;
} RMdvdSubPictureStream;

/**
   attributes of the Sub Picture Streams currently available.
 */
typedef struct {
	RMbool isAvailable[MAX_SPST];
	RMdvdSubPictureStream subPictureStreams[MAX_SPST];
} RMdvdSubPictureStreams;

/**
   Button location.
 */
typedef struct {
	RMuint16 left;
	RMuint16 right;
	RMuint16 top;
	RMuint16 bottom;
} RMdvdButtonInformation;

/** Button Information */
typedef struct {
	RMuint8 n;
	RMdvdButtonInformation buttons[MAX_BTN];
} RMdvdButtonsInformation;

/**
  DVD initialization structure.
  Contains the user preferences.
 */
typedef struct {
	/** SPRM(0). see VI4-158. */
	RMdvdLanguageCode menuDescriptionLanguageCode;
	/** SPRM(11). see VI4-169. */
	RMuint16 playerAudioMixingModeForKaraoke;

	/**
	   The country code used to set the parental level.
	   This is the value set in SPRM(12). see VI4-170
	 */
	RMdvdCountryCode countryCodeForParentalLevel;
	/**
	   The parental level. This is the value set 
	   in SPRM(13). see VI4-170.
	 */
	RMdvdParentalLevel parentalLevel;
	/**
	   Video display mode and aspect ratio. This corresponds
	   to the values set in SPRM(14). see VI4-171.
	   The possible values are:
	     - RM_DVD_VIDEO_16_9__4_3_PANSCAN: you have a 4/3 output screen. If
	       the input is 16/9 format, use panscan output. Otherwise, do not
	       rescale.
	     - RM_DVD_VIDEO_16_9__4_3_LETTERBOX: you have 4/3 output screen. If 
	       the input is 16/9 format, use letterbox output. Otherwise, do not
	       rescale.
	     - RM_DVD_VIDEO_4_3__16_9_ZOOM_OFF: you have 16/9 output screen. If 
	       the input is 4/3, just output it as-is. Do not rescale for 16/9
	       input.
	 */
	RMdvdVideoMode videoMode;
	/**
	   Audio Capability. This corresponds to the values
	   set in SPRM(15). see VI4-172.
	   It is a list of ORed RMdvdAudioCapabilities.
	   ie: 
	   audioCapability = !RM_DVD_CAN_SDDS_KARAOKE |
	                     !RM_DVD_CAN_DTS_KARAOKE |
			     !RM_DVD_CAN_MPEG_KARAOKE |
			     ...
	 */
	RMint16 audioCapability;
	/**
	   Initial Language code for Audio Stream. 
	   see VI4-173. SPRM(16) and SPRM(17).
	*/
	RMdvdLanguageCode initialLanguageForAudioStream;
	RMuint8 initialLanguageExtensionForAudioStream;

	/**
	   Initial Language code for SubPicture Stream. 
	   see VI4-174. SPRM(18) and SPRM(19).
	*/
	RMdvdLanguageCode initialLanguageForSubPictureStream;
	RMuint8 initialLanguageExtensionForSubPictureStream;

	RMbool initialSpuDisplayFlag;

	/** see SPRM(20). VI4-175. */
	RMdvdRegionCode playerRegionCode;
} RMdvdUserSettings;

/** GPRM Registers */
typedef RMuint16    RMdvdGPRMs[16];
/** SPRM Registers */
typedef RMuint16    RMdvdSPRMs[24];

/** 
  Indicates which user operation (UOP) commands are currently allowed by the digital video disc (DVD).

  @remarks DVD authors can insert UOP commands at almost any place on the disc to disallow a navigation command 
  that would otherwise be permitted within the current DVD domain. 
  In other words, UOP commands enable disc authors to override the usual navigation permissions. 
*/
typedef enum {
    RM_DVD_UOP_FLAG_Play_Title_Or_AtTime           = 0x00000001, 
    RM_DVD_UOP_FLAG_Play_Chapter                   = 0x00000002, 
    RM_DVD_UOP_FLAG_Play_Title                     = 0x00000004, 
    RM_DVD_UOP_FLAG_Stop                           = 0x00000008,  
    RM_DVD_UOP_FLAG_ReturnFromSubMenu              = 0x00000010,
    RM_DVD_UOP_FLAG_Play_Chapter_Or_AtTime         = 0x00000020, 
    RM_DVD_UOP_FLAG_PlayPrev_Or_Replay_Chapter     = 0x00000040,  
    RM_DVD_UOP_FLAG_PlayNext_Chapter               = 0x00000080,   
    RM_DVD_UOP_FLAG_Play_Forwards                  = 0x00000100,  
    RM_DVD_UOP_FLAG_Play_Backwards                 = 0x00000200,
    RM_DVD_UOP_FLAG_ShowMenu_Title                 = 0x00000400,
    RM_DVD_UOP_FLAG_ShowMenu_Root                  = 0x00000800,
    RM_DVD_UOP_FLAG_ShowMenu_SubPic                = 0x00001000,
    RM_DVD_UOP_FLAG_ShowMenu_Audio                 = 0x00002000,
    RM_DVD_UOP_FLAG_ShowMenu_Angle                 = 0x00004000,
    RM_DVD_UOP_FLAG_ShowMenu_Chapter               = 0x00008000,
    RM_DVD_UOP_FLAG_Resume                         = 0x00010000,
    RM_DVD_UOP_FLAG_Select_Or_Activate_Button      = 0x00020000,
    RM_DVD_UOP_FLAG_Still_Off                      = 0x00040000,
    RM_DVD_UOP_FLAG_Pause_On                       = 0x00080000,
    RM_DVD_UOP_FLAG_Select_Audio_Stream            = 0x00100000,
    RM_DVD_UOP_FLAG_Select_SubPic_Stream           = 0x00200000,
    RM_DVD_UOP_FLAG_Select_Angle                   = 0x00400000,
    RM_DVD_UOP_FLAG_Select_Karaoke_Audio_Presentation_Mode = 0x00800000,
    RM_DVD_UOP_FLAG_Select_Video_Mode_Preference   = 0x01000000 
} RMdvdValidUOPFlag;


/** playlist item type */
typedef enum {
	/** Play the chapter as defined by TTN and PTTN */
	RM_DVD_PLAYLIST_PLAY_CHAPTER,
	/** Play the chapter as defined by TTN */
	RM_DVD_PLAYLIST_PLAY_TITLE,
	/** End playlist mode. */
	RM_DVD_PLAYLIST_END
} RMdvdPlaylistItemType;
/** playlist item. */
typedef struct {
	/** item type.*/
	RMdvdPlaylistItemType type;
	/** TTN (title number) for this item if meaningful */
	RMuint8 TTN;
	/** PTTN (chapter number) for this item if meaningful */
	RMuint16 PTTN;
} RMdvdPlaylistItem;


/** Macrovision Levels, see VI4-107 */
typedef enum {
	RM_DVD_MACROVISION_DISABLED = 0,
	RM_DVD_MACROVISION_LEVEL1   = 1,
	RM_DVD_MACROVISION_LEVEL2   = 2,
	RM_DVD_MACROVISION_LEVEL3   = 3
} RMdvdMacrovisionLevel;

typedef enum
{
	// DVD video
	FILE_VMGI = 555,
	FILE_VMGM_VOBS,
	FILE_VMGI_BUP,
	FILE_VTSI, 
	FILE_VTSM_VOBS,
	FILE_VTSTT_VOBS,
	FILE_VTSI_BUP,
	// DVD audio
	FILE_SAMG,
	FILE_AMGI,
	FILE_AMGM_VOBS,
	FILE_AMGI_BUP,
	FILE_ASVSI,
	FILE_ASVOBS,
	FILE_ASVSI_BUP,
	FILE_ATSI,
	FILE_AOTT_AOBS,
	FILE_ATSI_BUP,
	FILE_MKB,
	FILE_MKB_BUP,
	// DVD+VR
	FILE_VRMI,
	FILE_VRMI_BUP,
	FILE_VRM_SCRATCH,
	// DVD-VR
	FILE_RTR_VMG,
	FILE_MOVIE_VRO,
	FILE_STILL_VRO,
	FILE_AUDIO_VRO,
	FILE_RTR_VMG_BUP,
} RMdvdFileType;

/** TV TYPE */
typedef enum {
	RM_TV_4_3 = 774,
	RM_TV_16_9,
} RMTvTypes;

typedef enum
{
	RM_NO_ENCRYPTION = 879,
	RM_CSS_ENCRYPTION,
	RM_CPPM_ENCRYPTION
}RMdvdEncryptionType;


/**
	Title Information
	see VI4-12
*/
typedef struct {
	RMbool OneSequentialPGC;
	RMuint8 MenuExistence;
	RMuint8 AGL_Ns; // number of angles
	RMuint16 PTT_Ns; // number of chapters
	RMuint32 PB_TM; // playback time (in tenths of second)
	RMdvdVideoStream VST;
	RMdvdAudioStreams AST;
	RMdvdSubPictureStreams SPST;

} RMdvdTitleInfo;
	
#endif // __DVDNAV_H__
