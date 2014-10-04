" add project include directory path for include completion
let root  = unite#util#path2project_directory(expand('%'))
let inc_dir = root."/project/server/include"
let a = isdirectory(inc_dir)
if isdirectory(inc_dir)
	execute "setlocal path+=".inc_dir
endif

" library tag directories
setlocal tags+=~/raspi-dev/opt/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/arm-linux-gnueabihf/include/c++/4.8.3/tags
setlocal tags+=~/raspi-dev/opt/rootfs/usr/local/include/tags
