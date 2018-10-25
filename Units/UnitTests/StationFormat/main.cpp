#include <Units\StationFormat.h>
#include <iostream>

int main(void)
{
   Float64 station = 123456.7890;
   unitStationFormat si_format(unitStationFormat::Meter);
   unitStationFormat us_format(unitStationFormat::Feet);

   std::cout << "Station value in system units : " << station << std::endl;
   std::cout << "SI Station format : " << si_format.AsString( station ).c_str() << std::endl;
   std::cout << "US Station format : " << us_format.AsString( station ).c_str() << std::endl;

   std::string si_station_str("1+123.32123");
   std::string us_station_str("11+23.32123");
   std::cout << "SI Station String : " << si_station_str.c_str() << std::endl;
   std::cout << "SI Station String in system units : " << si_format.FromString( si_station_str ) << std::endl;
   std::cout << "US Station String : " << us_station_str.c_str() << std::endl;
   std::cout << "US Station String in system units : " << us_format.FromString( us_station_str ) << std::endl;

   Float64 v;
   try
   {
      std::cout << "Get station value from si formater using us formated string" << std::endl;
      v = si_format.FromString( us_station_str );
   }
   catch( unitXStationFormat& e )
   {
      std::cout << "Caught the exception" << std::endl;
      std::cout << "Why : " << e.Why() << std::endl;
      std::cout << "File : " << e.File() << std::endl;
      std::cout << "Line : " << e.Line() << std::endl;
      std::cout << "Offending String : " << e.GetOffendingString() << std::endl;
      std::cout << "Unit Of Measure : " << (e.GetUnitOfMeasure() == unitStationFormat::Meter?"Meter":"Feet") << std::endl;
   }

   try
   {
      std::cout << "Get station value from us formater using is formated string" << std::endl;
      v = us_format.FromString( si_station_str );
   }
   catch( unitXStationFormat& e )
   {
      std::cout << "Caught the exception" << std::endl;
      std::cout << "Why : " << e.Why() << std::endl;
      std::cout << "File : " << e.File() << std::endl;
      std::cout << "Line : " << e.Line() << std::endl;
      std::cout << "Offending String : " << e.GetOffendingString() << std::endl;
      std::cout << "Unit Of Measure : " << (e.GetUnitOfMeasure() == unitStationFormat::Meter?"Meter":"Feet") << std::endl;
   }

   std::string bad_string1("abcdefg+hij.xyz");
   std::cout << bad_string1.c_str() << " "
             << (si_format.IsValidString(bad_string1)?"is a":"is not a")
             << " valid string using si format" << std::endl;
   std::cout << bad_string1.c_str() << " "
             << (si_format.IsValidString(bad_string1)?"is a":"is not a")
             << " valid string using us format" << std::endl;

   std::string bad_string2("1233654.3654");
   std::cout << bad_string2.c_str() << " "
             << (si_format.IsValidString(bad_string2)?"is a":"is not a")
             << " valid string using si format" << std::endl;
   std::cout << bad_string2.c_str() << " "
             << (si_format.IsValidString(bad_string2)?"is a":"is not a")
             << " valid string using us format" << std::endl;

   std::string bad_string3("+32.32");
   std::cout << bad_string3.c_str() << " "
             << (si_format.IsValidString(bad_string3)?"is a":"is not a")
             << " valid string using si format" << std::endl;
   std::cout << bad_string3.c_str() << " "
             << (si_format.IsValidString(bad_string3)?"is a":"is not a")
             << " valid string using us format" << std::endl;

   return 1;
}