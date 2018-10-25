#include <iostream>
#include <fstream>
#include <GraphicsLib\PointMapper.h>
using namespace std;

// Test file format
// Line 1: output file name
// Line 2: Device Origin x y
// Line 3: Device Extents dx dy
// Line 4: World Origin x y
// Line 5: World Extents wx wy
// Line 6: Number of scales
// Line 6a...  Scale
// Line 7: Pixel Density x y
// Line 8: Number of test points
// Line 8a...  MapMode MapDirection X Y
//
// MapMode constants
// Anisotropic                            1
// Isotropic                              2
// Anisotropic | BestFitX                 5
// Anisotropic | BestFitY                 9
// Anisotropic | BestFitX | BestFitY     13
// Isotropic   | BestFitX                 6
// Isotropic   | BestFitY                10
// Isotropic   | BestFitX | BestFitY     14
//
// MapDirection constants
// WP to DP   0
// DP to WP   1

#define ANISOTROPIC  0x0001L
#define ISOTROPIC    0x0002L
#define BESTFITX     0x0004L
#define BESTFITY     0x0008L

void write_WPtoDP(ostream& os,double wx,double wy,long dx,long dy)
{
   os << "WP(" << wx << "," << wy << ") = DP(" << dx << "," << dy << ")" << endl;
}

void write_DPtoWP(ostream& os,long dx,long dy,double wx,double wy)
{
   os << "DP(" << dx << "," << dy << ") = WP(" << wx << "," << wy << ")" << endl;
}

void write_map_mode(ostream& os,grlibPointMapper::MapMode mapmode,grlibPointMapper::MapModeModifier mmm)
{
   os << "Map Mode: ";

   if (mapmode == grlibPointMapper::Anisotropic)
      os << "Anisotropic";
   else if (mapmode == grlibPointMapper::Isotropic)
      os << "Isotropic";
   else
      os << "Bad";

   if (mmm == grlibPointMapper::BestFitX)
      os << " | BestFitX";
   else if ( mmm == grlibPointMapper::BestFitY)
      os << " | BestFitY";
   else if ( mmm == grlibPointMapper::BestFitXY)
      os << " | BestFitXY";
   else if ( mmm != grlibPointMapper::NoFit)
      os << " | bad";

   os << endl;
}

int main(int argc, char *argv[])
{
   if (argc <= 1)
   {
      cout << "Usage: PointMapperTest testdata" << endl;
      return 1;
   }


   ifstream ifile(argv[1]);
   if (!ifile)
   {
      cout << "Error opening " << argv[2] << endl;
      return 1;
   }

   char buffer[256];
   ifile.getline(buffer,sizeof(buffer));

   ofstream ofile(buffer);
   if (!ofile)
   {
      cout << "Error opening " << buffer << endl;
      return 1;
   }

   ofile << "Unit test for class PointMapper" << endl;
   ofile << "===============================" << endl << endl;


   double wx,wy;
   long dx,dy;
   grlibPointMapper mapper;


   ofile << "Device Data" << endl;
   ofile << "===========" << endl << endl;

   ifile >> dx >> dy;
   ofile << "Device Origin x = " << dx << " y = " << dy << endl;
   mapper.SetDeviceOrg(dx,dy);

   ifile >> dx >> dy;
   ofile << "Device Extents dx = " << dx << " dy = " << dy << endl;
   mapper.SetDeviceExt(dx,dy);

   ofile << endl;

   ofile << "World Data" << endl;
   ofile << "==========" << endl << endl;

   ifile >> wx >> wy;
   ofile << "World Origin x = " << wx << " y = " << wy << endl;
   mapper.SetWorldOrg(wx,wy);

   ifile >> wx >> wy;
   ofile << "World Extends wx = " << wx << " wy = " << wy << endl;
   mapper.SetWorldExt(wx,wy);

   ofile << endl;

   int num_scales;
   double scale;
   ofile << "Scales" << endl;
   ofile << "======" << endl;

   ifile >> num_scales;
   for (int i = 0; i < num_scales; i++)
   {
      ifile >> scale;
      ofile << scale << endl;
      mapper.AddScale(scale);
   }

   ofile << endl;

   double pixel_density_x, pixel_density_y;
   ifile >> pixel_density_x >> pixel_density_y;
   ofile << "Pixel Density X = " << pixel_density_x << endl;
   ofile << "Pixel Density Y = " << pixel_density_y << endl << endl;
   mapper.SetPixelDensity(pixel_density_x,pixel_density_y);


   int num_test_points;
   int map_direction;
   long mapping;
   grlibPointMapper::MapMode mode;
   grlibPointMapper::MapModeModifier modifier;
   
   ofile << "Test Points" << endl;
   ofile << "===========" << endl;
   ofile << endl;

   ifile >> num_test_points;
   for (int p = 0; p < num_test_points; p++)
   {
      ifile >> mapping >> map_direction >> wx >> wy;

      if ( mapping & ANISOTROPIC )
         mode = grlibPointMapper::Anisotropic;
      else
         mode = grlibPointMapper::Isotropic;

      if ( (mapping & BESTFITX) && (mapping & BESTFITY) )
         modifier = grlibPointMapper::BestFitXY;
      else if ( mapping & BESTFITX ) 
         modifier = grlibPointMapper::BestFitX;
      else if ( mapping & BESTFITY )
         modifier = grlibPointMapper::BestFitY;
      else
         modifier = grlibPointMapper::NoFit;


      ofile << "Point: " << p << endl;
      write_map_mode(ofile,mode,modifier);
      mapper.SetMappingMode(mode);
      mapper.SetMappingModeModifier(modifier);

      if (map_direction == 1)
      {
         // map_direction == 1 -> DPtoWP
         dx = (long)wx;
         dy = (long)wy;

         mapper.DPtoWP(dx,dy,&wx,&wy);
         write_DPtoWP(ofile,dx,dy,wx,wy);
      }
      else
      {
         mapper.WPtoDP(wx,wy,&dx,&dy);
         write_WPtoDP(ofile,wx,wy,dx,dy);
      }

      ofile << endl;
   }

   ofile.close();
   ifile.close();

   return 0;
}