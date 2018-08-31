export ASAN_OPTIONS := detect_leaks=1
export CC := /usr/local/opt/llvm/bin/clang
export CXX := /usr/local/opt/llvm/bin/clang++
export BUILD_DIRECTORY := Build
export INPUT_DIRECTORY := Input
export PROGRAM := yambi

.PHONY: clean compile

all: lint

lint: run
	@printf '\n✨ Lint\n'
	@oclint -p Build -no-analytics -enable-global-analysis \
	        -enable-clang-static-analyzer Source/*.cpp

run: test
	@printf '🚗 Run\n\n'
	@$(BUILD_DIRECTORY)/$(PROGRAM) \
		$(INPUT_DIRECTORY)/"Plain Scalar>Word Chars.yaml"

test: compile
	@printf '🐛 Test\n\n'
	@Test/test.fish && printf '\n'

compile: $(BUILD_DIRECTORY)
	@printf '🏗 Build\n\n'
	@set -o pipefail; ninja -C Build | sed -e 's~\.\./~~' && printf '\n';

$(BUILD_DIRECTORY):
	@printf '🤖 Configure\n\n'
	@mkdir -p $(BUILD_DIRECTORY)
	@cd $(BUILD_DIRECTORY); set -o pipefail; \
		cmake -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .. && printf '\n'

clean:
	@printf '🗑 Clean\n'
	@rm -rf $(BUILD_DIRECTORY)
