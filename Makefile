.DEFAULT_GOAL := build_test
mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(patsubst %/,%,$(dir $(mkfile_path)))

build_test:
	echo $(current_dir)
	mkdir -p $(current_dir)/workDir/test
	mkdir -p $(current_dir)/workDir/test/build
	cmake -D CMAKE_BUILD_TYPE=Debug -D EXECUTABLE_OUTPUT_PATH=$(current_dir)/workDir/test -D LIBRARY_OUTPUT_PATH=$(current_dir)/workDir/test -B$(current_dir)/workDir/test/build -H$(current_dir)/
	make -C $(current_dir)/workDir/test/build -j `nproc` VERBOSE=1
run_test: build_test
	$(current_dir)/Workflow/scripts/testRun.py -w $(current_dir)
release: install_release

install_release: build_release
	$(eval MSG=$(shell git tag -l --format="%(contents)" -n99 ${VER}))
ifneq (, $(shell which ~/bin/ccs/addProject))
	~/bin/ccs/addProject -d $(current_dir)/description.yaml -f $(current_dir)/workDir/${VER}/CalcProj -r ${VER} -c "${MSG}"
endif

build_release: pre_release
	$(eval VER=$(shell $(current_dir)/Workflow/scripts/tagsManager.py -w $(current_dir)))
	rm -rf $(current_dir)/workDir/${VER}
	mkdir $(current_dir)/workDir/${VER}
	mkdir $(current_dir)/workDir/${VER}/build
	cmake -D CMAKE_BUILD_TYPE=Release -D EXECUTABLE_OUTPUT_PATH=$(current_dir)/workDir/${VER} -D LIBRARY_OUTPUT_PATH=$(current_dir)/workDir/${VER} -B$(current_dir)/workDir/${VER}/build -H$(current_dir)/
	make -C $(current_dir)/workDir/${VER}/build -j `nproc` VERBOSE=1

pre_release: 
ifneq ($(shell git status --porcelain), )
	$(error There is uncommited changes)
endif
ifdef MSG
	$(current_dir)/Workflow/scripts/tagsManager.py -w $(current_dir) -m "${MSG}"
else
	$(current_dir)/Workflow/scripts/tagsManager.py -w $(current_dir)
endif
