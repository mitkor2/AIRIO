# invoke SourceDir generated makefile for debug.pem4f
debug.pem4f: .libraries,debug.pem4f
.libraries,debug.pem4f: package/cfg/debug_pem4f.xdl
	$(MAKE) -f E:\Intership\Other_projects\MsysCode\tirtos_builds_MSP_EXP432P401R_debug_ccs/src/makefile.libs

clean::
	$(MAKE) -f E:\Intership\Other_projects\MsysCode\tirtos_builds_MSP_EXP432P401R_debug_ccs/src/makefile.libs clean

