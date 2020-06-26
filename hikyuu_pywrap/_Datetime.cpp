/*
 * _Datetime.cpp
 *
 *  Created on: 2012-9-27
 *      Author: fasiondog
 */

#include <boost/python.hpp>
#include <hikyuu/serialization/Datetime_serialization.h>
#include "pickle_support.h"

using namespace boost::python;
using namespace hku;

bool (*eq)(const Datetime&, const Datetime&) = operator==;
bool (*ne)(const Datetime&, const Datetime&) = operator!=;
bool (*gt)(const Datetime&, const Datetime&) = operator>;
bool (*lt)(const Datetime&, const Datetime&) = operator<;
bool (*ge)(const Datetime&, const Datetime&) = operator>=;
bool (*le)(const Datetime&, const Datetime&) = operator<=;

void export_Datetime() {
    class_<Datetime>("Datetime",
                     R"(日期时间类（精确到微秒），通过以下方式构建：
    
    - 通过字符串：Datetime("2010-1-1 10:00:00")、Datetime("2001-1-1")、
                 Datetime("20010101")、Datetime("20010101T232359)
    - 通过 Python 的date：Datetime(date(2010,1,1))
    - 通过 Python 的datetime：Datetime(datetime(2010,1,1,10)
    - 通过 YYYYMMDDHHMM 或 YYYYMMDD 形式的整数：Datetime(201001011000)、Datetime(20010101)
    - Datetime(year, month, day, hour=0, minute=0, second=0, millisecond=0, microsecond=0))")

      .def(init<>())
      .def(init<const std::string&>())
      .def(init<unsigned long long>())
      .def(init<long, long, long, long, long, long, long, long>(
        (arg("year"), arg("month"), arg("day"), arg("hour") = 0, arg("minute") = 0,
         arg("second") = 0, arg("millisecond") = 0, arg("microsecond") = 0)))

      .def("__str__", &Datetime::str)
      .def("__repr__", &Datetime::repr)

      .add_property("year", &Datetime::year, "年")
      .add_property("month", &Datetime::month, "月")
      .add_property("day", &Datetime::day, "日")
      .add_property("hour", &Datetime::hour, "时")
      .add_property("minute", &Datetime::minute, "分")
      .add_property("second", &Datetime::second, "秒")
      .add_property("millisecond", &Datetime::millisecond, "毫秒")
      .add_property("microsecond", &Datetime::microsecond, "微秒")
      .add_property("number", &Datetime::number)

      .def("isNull", &Datetime::isNull, "\n是否是Null值，等于 Datetime() 直接创建的对象")

      .def("dayOfWeek", &Datetime::dayOfWeek, "\n返回是一周中的第几天，周日为0，周一为1")
      .def("dayOfYear", &Datetime::dayOfYear, "\n返回一年中的第几天，1月1日为一年中的第1天")
      .def("startOfDay", &Datetime::startOfDay, "\n返回当天 0点0分0秒")
      .def("endOfDay", &Datetime::endOfDay, "\n返回当日 23点59分59秒")
      .def("nextDay", &Datetime::nextDay, "\n返回下一自然日")
      .def("nextWeek", &Datetime::nextWeek, "\n返回下周周一日期")
      .def("nextMonth", &Datetime::nextMonth, "\n返回下月首日日期")
      .def("nextQuarter", &Datetime::nextQuarter, "\n返回下一季度首日日期")
      .def("nextHalfyear", &Datetime::nextHalfyear, "\n返回下一半年度首日日期")
      .def("nextYear", &Datetime::nextYear, "\n返回下一年度首日日期")
      .def("preDay", &Datetime::preDay, "\n返回前一自然日日期")
      .def("preWeek", &Datetime::preWeek, "\n返回上周周一日期")
      .def("preMonth", &Datetime::preMonth, "\n返回上月首日日期")
      .def("preQuarter", &Datetime::preQuarter, "\n返回上一季度首日日期")
      .def("preHalfyear", &Datetime::preHalfyear, "\n返回上一半年度首日日期")
      .def("preYear", &Datetime::preYear, "\n返回上一年度首日日期")
      .def("dateOfWeek", &Datetime::dateOfWeek,
           R"(
返回指定的本周中第几天的日期，周日为0天，周六为第6天
        
:param int day: 指明本周的第几天，如小于则认为为第0天，如大于6则认为为第6天)")

      .def("startOfWeek", &Datetime::startOfWeek, "\n返回周起始日期（周一）")
      .def("endOfWeek", &Datetime::endOfWeek, "\n返回周结束日期（周日）")
      .def("startOfMonth", &Datetime::startOfMonth, "\n返回月度起始日期")
      .def("endOfMonth", &Datetime::endOfMonth, "\n返回月末最后一天日期")
      .def("startOfQuarter", &Datetime::startOfQuarter)
      .def("endOfQuarter", &Datetime::endOfQuarter)
      .def("startOfHalfyear", &Datetime::startOfHalfyear)
      .def("endOfHalfyear", &Datetime::endOfHalfyear)
      .def("startOfYear", &Datetime::startOfYear)
      .def("endOfYear", &Datetime::endOfYear)
      .def("min", &Datetime::min)
      .staticmethod("min")
      .def("max", &Datetime::max)
      .staticmethod("max")
      .def("now", &Datetime::now)
      .staticmethod("now")
      .def("today", &Datetime::today)
      .staticmethod("today")
      //不支持boost.date
      //.def("date", &Datetime::date)
      .def("__eq__", eq)
      .def("__ne__", ne)
      .def("__gt__", gt)
      .def("__lt__", lt)
      .def("__ge__", ge)
      .def("__le__", le)

      .def("__add__", &Datetime::operator+)
      .def("__sub__", &Datetime::operator-)

#if HKU_PYTHON_SUPPORT_PICKLE
      .def_pickle(normal_pickle_suite<Datetime>())
#endif
      ;

    def("getDateRange", getDateRange, (arg("start"), arg("end")));
}
