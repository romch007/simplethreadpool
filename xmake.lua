add_rules("mode.debug", "mode.release")

set_rundir(".")
set_targetdir("./build/$(plat)_$(arch)_$(mode)")

includes("tests/xmake.lua")
includes("examples/xmake.lua")

target("threadpool")
    set_kind("static")
    add_files("src/*.cpp")
    add_headerfiles("include/(threadpool/*.hpp)")
    add_includedirs("include", { public = true })

