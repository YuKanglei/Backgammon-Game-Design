#pragma once
#include "point.hpp"

namespace utils {

class console_abstract{
    public:
        virtual ~console_abstract() {}

        /**
         * 需要用到的控制台操作函数
         * e.g.
         * virtual bool write(char character, const utils::point_uint & coordinate) = 0;
        */
        virtual bool write(char character, const utils::point_uint& coordinate) = 0;

        /**
        * 设置下一个字符的颜色
        * @param color 颜色值
        */
        virtual void set_color(int color) = 0;

        /**
        * 清除当前屏幕上的所有字符
        */
        virtual void clear() = 0;
};

} // namespace utils
