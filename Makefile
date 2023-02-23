

compile: build/tag
	cd build && meson compile

test: build/tag
	cd build && meson test

build/tag:
	if [ ! -d build ]; then meson setup build; fi
	touch build/tag

clean:
	rm -rf build

