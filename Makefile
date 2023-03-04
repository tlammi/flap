
.PHONY: compile test list-tests clean view-test-report

compile: build/tag
	@cd build && meson compile

test: build/tag
	@cd build && meson test "${TEST_SUITE}"

view-test-report:
	@less build/meson-logs/testlog.txt

list-tests:
	@cd build && meson test --list

build/tag:
	@if [ ! -d build ]; then meson setup build; fi
	@touch build/tag

clean:
	@rm -rf build

