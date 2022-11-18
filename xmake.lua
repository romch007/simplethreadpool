set_project("simplethreadpool")

set_version("1.0.0")

set_languages("cxx20")

add_rules("mode.debug", "mode.release", "mode.valgrind")

set_rundir(".")
set_targetdir("./build/$(plat)_$(arch)_$(mode)")

if is_plat("wasm") then
    add_cxxflags("-sPTHREAD_POOL_SIZE=20")
    add_cxxflags("-sALLOW_MEMORY_GROWTH")
    add_cxxflags("-pthread")
    add_ldflags("-sPTHREAD_POOL_SIZE=20")
    add_ldflags("-sALLOW_MEMORY_GROWTH")
    add_ldflags("-pthread")
    add_defines("__WASM__")
    if is_mode("debug") then
        add_cxxflags("-sASSERTIONS=2")
        add_cxxflags("-sSAFE_HEAP=1")
        add_cxxflags("-sDEMANGLE_SUPPORT=1")
    end
end

includes("tests/xmake.lua")
includes("examples/xmake.lua")

target("simplethreadpool")
    set_kind("$(kind)")
    set_group("Librairies")

    add_files("src/*.cpp")
    add_headerfiles("include/(simplethreadpool/*.hpp)")
    add_includedirs("include", { public = true })

    if is_plat("linux") then
        add_syslinks("pthread")
    end

    on_load(function (target)
        if target:kind() == "static" then
            target:add("defines", "SIMPLETHREADPOOL_STATIC", { public = true })
        end
    end)

