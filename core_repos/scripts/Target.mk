
Target.h: .config
	@awk '{\
			split($$0, a, "=");\
			if (substr(a[1], 0, 6) == "CONFIG") {\
				tmp = substr(a[1], 7); \
				if (substr(a[2],0,1) == "y") \
					printf("#define\tCONF%s\n", tmp); \
				else if (substr(a[2],0,1) == "n") \
					printf("#undef\tCONF%s\n", tmp); \
				else if (substr(a[2],0,1) == "") {\
				} else {\
					printf("#define\tCONF%s\t%s\n", tmp, substr($$0,length(a[1])+2)); \
				} \
			}\
	}' .config > Target.h

Target.options: .config
	@awk ' {\
		split($$0, a, "=");\
		if (substr(a[1], 0, 6) == "CONFIG") {\
			len = length($$0); len1 = length(a[1]);\
			tmp = substr(a[1], 7); \
			if (substr(a[2],0,1) == "y") \
				printf("export CONF%s=y\n", tmp); \
			else if (substr(a[2],0,1) == "\"") \
				printf("export CONF%s=%s\n", tmp, substr($$0, len1+3, len-len1-3)); \
			else \
				printf("export CONF%s=%s\n", tmp, substr($$0, len1+2, len-len1-1));  \
		}\
	}' .config > Target.options
	@( `grep CONF_PLATFORM_X86 Target.options`; if [ x$$CONF_PLATFORM_X86 == xy ]; then \
		RELATIVE_PATH_FOR_RESOURCES=`pwd`/build/root;\
		sed -i -e s,CONF_RELATIVE_PATH_FOR_RESOURCES=,CONF_RELATIVE_PATH_FOR_RESOURCES=$$RELATIVE_PATH_FOR_RESOURCES, Target.options;\
		sed -i -e s,CONF_RELATIVE_PATH_FOR_RESOURCES\\t\"\",CONF_RELATIVE_PATH_FOR_RESOURCES\\t\"$$RELATIVE_PATH_FOR_RESOURCES\", Target.h;\
	fi )

