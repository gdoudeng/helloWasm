do {
\#if COCOS2D_DEBUG >= 1
    if (!toluafix_isfunction(tolua_S, ${arg_idx}, "LUA_FUNCTION", 0, &tolua_err))
    {
        goto tolua_lerror;
    }
\#endif 
    LUA_FUNCTION handler = toluafix_ref_function(tolua_S, ${arg_idx}, 0);
    std::shared_ptr<LuaFunctionWrapper> func(new LuaFunctionWrapper(tolua_S, handler));
    auto lambda = [tolua_S, func](${lambda_parameters}) -> ${ret_type.name} {
        #set arg_count = len($param_types)
        #set $count = 0
        #while $count < $arg_count
            #set $arg = $param_types[$count]
            ${arg.from_native({"generator": $generator,
                "type_name": $arg.namespaced_name.replace("*", ""),
                "ntype": $arg.get_whole_name($generator),
                "level": 2,
                "scriptname": $generator.scriptname_from_native($arg.namespaced_name, $arg.namespace_name),
                "in_value": "larg" + str(count),
            })};
            #set $count = $count + 1
        #end while
        #if $ret_type.name != "void"
            ${ret_type.get_whole_name($generator)} ret;
            LuaEngine::getInstance()->getLuaStack()->executeFunction(func->getLuaFunction(), ${arg_count}, 1, [&ret](lua_State* _state, int numResults) -> void {
                #if $ret_type.is_pointer
                ret = dynamic_cast<${ret_type.get_whole_name($generator)}>(tolua_tousertype(_state, -1, nullptr))
                lua_pop(_state, 1);
                #elif $ret_type.name == "bool"
                ret = lua_toboolean(_state, -1);
                lua_pop(_state, 1); 
                #elif $ret_type.name == "std::string"
                ret = lua_tostring(_state, -1);
                lua_pop(_state, 1);
                #else
                ret = lua_tonumber(_state, -1);
                lua_pop(_state, 1);
                #end if
            });
            return ret;
        #else
            LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(func->getLuaFunction(), ${arg_count});
        #end if
    };
    ${out_value} = lambda;
} while(0)
