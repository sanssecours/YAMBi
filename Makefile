export ASAN_OPTIONS := detect_leaks=1
export CC := /usr/local/opt/llvm/bin/clang
export CXX := /usr/local/opt/llvm/bin/clang++
export BUILD_DIRECTORY := Build
export INPUT_DIRECTORY := Input
export PROGRAM := yambi

.PHONY: clean compile

run: compile
	@printf '🚗 Run\n\n'
	@$(BUILD_DIRECTORY)/$(PROGRAM) \
		$(INPUT_DIRECTORY)/"Plain Scalar>Word Chars.yaml"

compile: $(BUILD_DIRECTORY)
	@printf '🏗 Build\n\n'
	@ninja -C Build
	@printf '\n'

$(BUILD_DIRECTORY):
	@printf '🤖 Configure\n\n'
	@mkdir -p $(BUILD_DIRECTORY)
	@cd $(BUILD_DIRECTORY); cmake -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
	@printf '\n'

clean:
	@printf '🗑 Clean\n'
	@rm -rf $(BUILD_DIRECTORY)
