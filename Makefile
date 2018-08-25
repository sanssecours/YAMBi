export ASAN_OPTIONS := detect_leaks=1
export CC := /usr/local/opt/llvm/bin/clang
export CXX := /usr/local/opt/llvm/bin/clang++
export BUILD_DIRECTORY := Build

.PHONY: clean configure

configure:
	@mkdir -p $(BUILD_DIRECTORY)
	@cd $(BUILD_DIRECTORY); cmake -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..

clean:
	@printf '🗑 Clean\n'
	@rm -rf $(BUILD_DIRECTORY)
