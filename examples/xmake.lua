option("examples")
    set_default(false)
    set_showmenu(true)
    set_description("Build examples")
option_end()

if has_config("examples") then
    target("counter")
        set_kind("binary")
        set_group("Examples")
        add_files("counter.cpp")

        add_deps("threadpool")
end
