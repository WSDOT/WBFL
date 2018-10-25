#include <WBFL.h>

#include <Reporter\Report.h>
#include <Reporter\Chapter.h>
#include <Reporter\Paragraph.h>
#include <Reporter\HtmlReportVisitor.h>

#include <Reporter\ReportingUtils.h>
#include <Reporter\PageLayout.h>

#include <Reporter\RcFlowModifier.h>
#include <Reporter\RcFontModifier.h>

#include <Reporter\RcUnitTagT.h>
#include <Reporter\RcUnitValueT.h>
#include <Reporter\RcSectionValueT.h>
#include <Reporter\RcScalar.h>
#include <Reporter\RcSymbol.h>
#include <Reporter\RcDateTime.h>
#include <Reporter\RcHyperTarget.h>
#include <Reporter\RcImage.h>
#include <Reporter\RcString.h>
#include <Reporter\RcColor.h>
#include <Reporter\RcTable.h>
#include <Reporter\RcStation.h>

#include <Units\Measure.h>
#include <Units\StationFormat.h>

#include <iostream>
#include <fstream>

#define WRITE_UNIT(x,y) x.SetUnitOfMeasure( &y ); *p_paragraph << rptTab << x << rptNewLine;

int main(void)
{
   // Initialize the font styles   
   rptFontStyleLibrary* p_lib = rptFontStyleLibrary::Instance();

   // Setup some font styles
   rptRiStyle header1( rptRiStyle::SWISS, 16 );
   rptRiStyle header2( rptRiStyle::ROMAN, 12, true );
   rptRiStyle header3( rptRiStyle::MODERN, 10 );
   rptRiStyle header4( rptRiStyle::MODERN, 10, false, false, false, rptRiStyle::RED );
   rptRiStyle header5( rptRiStyle::MODERN, 10, false, false, false, rptRiStyle::BLUE );
   rptRiStyle colhead( rptRiStyle::SWISS, 10, true );
   rptRiStyle colnbr( rptRiStyle::MODERN, 10 );
   rptRiStyle colnbrc( colnbr );
   colnbrc.SetAlignment(rptRiStyle::CENTER);

   p_lib->AddNamedStyle("Header1", header1);
   p_lib->AddNamedStyle("Header2", header2);
   p_lib->AddNamedStyle("Header3", header3);
   p_lib->AddNamedStyle("Header4", header4);
   p_lib->AddNamedStyle("Header5", header5);
   p_lib->AddNamedStyle("ColumnHeader", colhead);
   p_lib->AddNamedStyle("ColumnNumber", colnbr);
   p_lib->AddNamedStyle("ColumnCentered", colnbrc);

   rptReport     report;
   rptChapter*   p_chapter   = new rptChapter;
   rptParagraph* p_paragraph = new rptParagraph;

   //
   // whip up some paragraphs and start sending some text
   //
   rptParagraph* p_para1 = new rptParagraph();
   *p_para1 << "****** It's Reporting Time: "
           << rptRcDateTime()
           << "******"
           << rptNewLine;

   // put in a hypertarget for here and a hyperlink to the bottom
   *p_para1 << new rptRcHyperTarget("The_Top");
   *p_para1 << new rptRcString("Link To The Bottom", "The_Bottom") << rptNewLine;
   *p_para1 << new rptRcString("Link To The Table",  "The_Table") << rptNewLine;

   *p_para1 << new rptRcImage("f:\\wbfl\\wsdotlogo.gif","WSDOT Logo") << rptNewLine;

   rptRcDateTime my_time;
   my_time.EnablePrintDate(false);
   *p_para1 << "The current time: "<< my_time <<rptNewLine;

   my_time.EnablePrintDate(true);
   my_time.EnablePrintTime(false);
   *p_para1 << "The current date: "<< my_time <<rptNewLine;

   char mc = 'c';
   *p_para1 << "To the right of me is a char " 
           << mc
           << " and an in-line "
           << 'c' 
           << rptNewLine;
   *p_chapter << p_para1;

   //
   // Units
   //
   *p_paragraph << rptNewLine << rptNewLine;
   *p_paragraph << "**************** Unit Value Stuff *************" << rptNewLine;
   *p_paragraph << "        (using direct units of measure)" << rptNewLine;

   Float64 value = 1.;
   rptRcScalar scalar( value );
   *p_paragraph << "The scalar value is " << scalar << rptNewLine;

   *p_paragraph << "Mass" << rptNewLine;
   rptMassUnitValue mass(value,&unitMeasure::Kilogram);
   WRITE_UNIT( mass, unitMeasure::Kilogram );
   WRITE_UNIT( mass, unitMeasure::Gram );
   WRITE_UNIT( mass, unitMeasure::MetricTon );
   WRITE_UNIT( mass, unitMeasure::Slug );
   WRITE_UNIT( mass, unitMeasure::PoundMass );

   *p_paragraph << rptNewLine;

   *p_paragraph << "Length" << rptNewLine;
   rptLengthUnitValue length(value,&unitMeasure::Meter);
   WRITE_UNIT( length, unitMeasure::Meter );
   WRITE_UNIT( length, unitMeasure::Millimeter );
   WRITE_UNIT( length, unitMeasure::Centimeter );
   WRITE_UNIT( length, unitMeasure::Kilometer );
   WRITE_UNIT( length, unitMeasure::Feet );
   WRITE_UNIT( length, unitMeasure::Inch );
   WRITE_UNIT( length, unitMeasure::Yard );
   WRITE_UNIT( length, unitMeasure::Mile );

   *p_paragraph << rptNewLine;

   *p_paragraph << "Length2" << rptNewLine;
   rptLength2UnitValue length2(value,&unitMeasure::Meter2);
   WRITE_UNIT( length2, unitMeasure::Meter2 );
   WRITE_UNIT( length2, unitMeasure::Millimeter2 );
   WRITE_UNIT( length2, unitMeasure::Centimeter2 );
   WRITE_UNIT( length2, unitMeasure::Kilometer2 );
   WRITE_UNIT( length2, unitMeasure::Feet2 );
   WRITE_UNIT( length2, unitMeasure::Inch2 );
   WRITE_UNIT( length2, unitMeasure::Yard2 );
   WRITE_UNIT( length2, unitMeasure::Mile2 );

   *p_paragraph << rptNewLine;

   *p_paragraph << "Length3" << rptNewLine;
   rptLength3UnitValue length3(value,&unitMeasure::Meter3);
   WRITE_UNIT( length3, unitMeasure::Meter3 );
   WRITE_UNIT( length3, unitMeasure::Millimeter3 );
   WRITE_UNIT( length3, unitMeasure::Centimeter3 );
   WRITE_UNIT( length3, unitMeasure::Kilometer3 );
   WRITE_UNIT( length3, unitMeasure::Feet3 );
   WRITE_UNIT( length3, unitMeasure::Inch3 );
   WRITE_UNIT( length3, unitMeasure::Yard3 );
   WRITE_UNIT( length3, unitMeasure::Mile3 );

   *p_paragraph << rptNewLine;

   *p_paragraph << "Length4" << rptNewLine;
   rptLength4UnitValue length4(value,&unitMeasure::Meter4);
   WRITE_UNIT( length4, unitMeasure::Meter4 );
   WRITE_UNIT( length4, unitMeasure::Millimeter4 );
   WRITE_UNIT( length4, unitMeasure::Centimeter4 );
   WRITE_UNIT( length4, unitMeasure::Kilometer4 );
   WRITE_UNIT( length4, unitMeasure::Feet4 );
   WRITE_UNIT( length4, unitMeasure::Inch4 );
   WRITE_UNIT( length4, unitMeasure::Yard4 );
   WRITE_UNIT( length4, unitMeasure::Mile4 );

   *p_paragraph << rptNewLine;

   *p_paragraph << "Time" << rptNewLine;
   rptTimeUnitValue time(value,&unitMeasure::Second);
   WRITE_UNIT( time, unitMeasure::Second );
   WRITE_UNIT( time, unitMeasure::Minute );
   WRITE_UNIT( time, unitMeasure::Hour );
   WRITE_UNIT( time, unitMeasure::Day );

   *p_paragraph << rptNewLine;

   *p_paragraph << "Temperature" << rptNewLine;
   rptTemperatureUnitValue temperature(value,&unitMeasure::Celcius);
   WRITE_UNIT( temperature, unitMeasure::Celcius );
   WRITE_UNIT( temperature, unitMeasure::Fahrenheit );

   *p_paragraph << rptNewLine;

   *p_paragraph << "Angle" << rptNewLine;
   rptAngleUnitValue angle(value,&unitMeasure::Radian);
   WRITE_UNIT( angle, unitMeasure::Radian );   
   WRITE_UNIT( angle, unitMeasure::Degree );   

   *p_paragraph << rptNewLine;

   *p_paragraph << "Pressure" << rptNewLine;
   rptPressureUnitValue pressure(value,&unitMeasure::Pa);
   WRITE_UNIT( pressure, unitMeasure::Pa );   
   WRITE_UNIT( pressure, unitMeasure::kPa );   
   WRITE_UNIT( pressure, unitMeasure::MPa );   
   WRITE_UNIT( pressure, unitMeasure::PSI );   
   WRITE_UNIT( pressure, unitMeasure::PSF );   
   WRITE_UNIT( pressure, unitMeasure::KSI );   
   WRITE_UNIT( pressure, unitMeasure::KSF );   

   *p_paragraph << rptNewLine;

   *p_paragraph << "Stress" << rptNewLine;
   rptStressUnitValue stress(value,&unitMeasure::Pa);
   WRITE_UNIT( stress, unitMeasure::Pa );   
   WRITE_UNIT( stress, unitMeasure::kPa );   
   WRITE_UNIT( stress, unitMeasure::MPa );   
   WRITE_UNIT( stress, unitMeasure::PSI );   
   WRITE_UNIT( stress, unitMeasure::PSF );   
   WRITE_UNIT( stress, unitMeasure::KSI );   
   WRITE_UNIT( stress, unitMeasure::KSF );   

   *p_paragraph << rptNewLine;

   *p_paragraph << "Unit Weight" << rptNewLine;
   rptUnitWeightUnitValue unit_weight(value,&unitMeasure::NewtonPerMeter3);
   WRITE_UNIT( unit_weight, unitMeasure::NewtonPerMeter3 );   
   WRITE_UNIT( unit_weight, unitMeasure::PCI );   
   WRITE_UNIT( unit_weight, unitMeasure::PCF );   

   *p_paragraph << rptNewLine;

   *p_paragraph << "Density" << rptNewLine;
   rptDensityUnitValue density(value,&unitMeasure::KgPerMeter3);
   WRITE_UNIT( density, unitMeasure::KgPerMeter3 );   
   WRITE_UNIT( density, unitMeasure::LbmPerFeet3 );   
   WRITE_UNIT( density, unitMeasure::SlugPerFeet3 );   

   *p_paragraph << rptNewLine;

   *p_paragraph << "Force" << rptNewLine;
   rptForceUnitValue force(value,&unitMeasure::Newton);
   WRITE_UNIT( force, unitMeasure::Newton );   
   WRITE_UNIT( force, unitMeasure::Kilonewton );   
   WRITE_UNIT( force, unitMeasure::Pound );   
   WRITE_UNIT( force, unitMeasure::Kip );   
   WRITE_UNIT( force, unitMeasure::Ton );   

   *p_paragraph << rptNewLine;

   *p_paragraph << "Force Per Length" << rptNewLine;
   rptForcePerLengthUnitValue force_per_length(value,&unitMeasure::NewtonPerMeter);
   WRITE_UNIT( force_per_length, unitMeasure::NewtonPerMeter );   
   WRITE_UNIT( force_per_length, unitMeasure::NewtonPerMillimeter );   
   WRITE_UNIT( force_per_length, unitMeasure::LbfPerFoot );   
   WRITE_UNIT( force_per_length, unitMeasure::LbfPerInch );   
   WRITE_UNIT( force_per_length, unitMeasure::KipPerFoot );   
   WRITE_UNIT( force_per_length, unitMeasure::KipPerInch );   

   *p_paragraph << rptNewLine;

   *p_paragraph << "Moment Per Angle" << rptNewLine;
   rptMomentPerAngleUnitValue moment_per_angle(value,&unitMeasure::NewtonMeterPerRadian);
   WRITE_UNIT( moment_per_angle, unitMeasure::NewtonMeterPerRadian );   
   WRITE_UNIT( moment_per_angle, unitMeasure::KiloNewtonMeterPerRadian );   
   WRITE_UNIT( moment_per_angle, unitMeasure::KipInchPerRadian );   
   WRITE_UNIT( moment_per_angle, unitMeasure::KipFeetPerRadian );   

   *p_paragraph << rptNewLine;

   *p_paragraph << "Moment" << rptNewLine;
   rptMomentUnitValue moment(value,&unitMeasure::NewtonMeter);
   WRITE_UNIT( moment, unitMeasure::NewtonMeter );   
   WRITE_UNIT( moment, unitMeasure::KilonewtonMeter );   
   WRITE_UNIT( moment, unitMeasure::InchLbf );   
   WRITE_UNIT( moment, unitMeasure::KipFeet );   

   *p_paragraph << rptNewLine;
   *p_paragraph << "Section Value" << rptNewLine;
   sysSectionValue sv(-10,10);
   rptMomentSectionValue sv_moment(sv,&unitMeasure::NewtonMeter );
   *p_paragraph << sv_moment << rptNewLine;

   *p_paragraph << rptNewLine;
   *p_paragraph << "Stations" << rptNewLine;
   rptRcStation si_station(123456.7890,&unitStationFormats::SI);
   rptRcStation us_station(123456.7890,&unitStationFormats::US);
   *p_paragraph << "SI Units " << si_station << rptNewLine;
   *p_paragraph << "US Units " << us_station << rptNewLine;

   *p_chapter << p_paragraph;

   //
   // Font and Flow Modifiers
   //
   rptParagraph* pMyPar = new rptParagraph();

   *pMyPar<< rptNewLine << rptNewLine << "********** Font Modifier Stuff *********"<<rptNewLine;
   *pMyPar<< bold(ON) << " Test bold " << bold(OFF) << rptNewLine;
   *pMyPar<< italic(ON) << " Test italic " << italic(OFF) << rptNewLine;
   *pMyPar<< underline(ON) << " Test underline " << underline(OFF) << rptNewLine;
   *pMyPar<< " Test Sub"<<subscript(ON)<<"script"<<subscript(OFF) << rptNewLine;
   *pMyPar<< " Test Super"<<superscript(ON)<<"script"<<superscript(OFF) << rptNewLine;

   *pMyPar<< rptNewPage << "Let's Start Out on a New Page"<< rptNewLine;

   //
   // Symbols
   //
   *pMyPar<< rptNewLine << rptNewLine << "********** Let's try some symbols *********"<<rptNewLine;
   *pMyPar<< new rptRcSymbol(rptRcSymbol::alpha) << " - alpha"<< rptNewLine;
   *pMyPar<< symbol(ALPHA) << "  - ALPHA" << rptNewLine;
   *pMyPar<< symbol(beta ) << "  - beta " << rptNewLine;
   *pMyPar<< symbol(BETA ) << "  - BETA " << rptNewLine;
   *pMyPar<< symbol(delta) << "  - delta" << rptNewLine;
   *pMyPar<< symbol(DELTA) << "  - DELTA" << rptNewLine;
   *pMyPar<< symbol(eta  ) << "  - eta  " << rptNewLine;
   *pMyPar<< symbol(ETA  ) << "  - ETA  " << rptNewLine;
   *pMyPar<< symbol(gamma) << "  - gamma" << rptNewLine;
   *pMyPar<< symbol(GAMMA) << "  - GAMMA" << rptNewLine;
   *pMyPar<< symbol(phi  ) << "  - phi  " << rptNewLine;
   *pMyPar<< symbol(PHI  ) << "  - PHI  " << rptNewLine;
   *pMyPar<< symbol(pi   ) << "  - pi  " << rptNewLine;
   *pMyPar<< symbol(PI   ) << "  - PI  " << rptNewLine;
   *pMyPar<< symbol(psi  ) << "  - psi  " << rptNewLine;
   *pMyPar<< symbol(PSI  ) << "  - PSI  " << rptNewLine;
   *pMyPar<< symbol(SIGMA) << "  - SIGMA" << rptNewLine;
   *pMyPar<< symbol(sigma) << "  - sigma" << rptNewLine;
   *pMyPar<< symbol(theta) << "  - theta" << rptNewLine;
   *pMyPar<< symbol(THETA) << "  - THETA" << rptNewLine;
   *pMyPar<< symbol(nu)    << "  - nu" << rptNewLine;
   *pMyPar<< symbol(NU)    << "  - NU" << rptNewLine;
   *pMyPar<< symbol(mu)    << "  - mu" << rptNewLine;
   *pMyPar<< symbol(MU)    << "  - MU" << rptNewLine;
   *pMyPar<< symbol(lambda)<< "  - lambda" << rptNewLine;
   *pMyPar<< symbol(LAMBDA)<< "  - LAMBDA" << rptNewLine;
   *pMyPar<< symbol(kappa) << "  - kappa" << rptNewLine;
   *pMyPar<< symbol(KAPPA)    << "  - KAPPA" << rptNewLine;
   *pMyPar<< symbol(nu)    << "  - nu" << rptNewLine;
   *pMyPar<< symbol(NU)    << "  - NU" << rptNewLine;
   *pMyPar<< symbol(omega) << "  - omega" << rptNewLine;
   *pMyPar<< symbol(OMEGA) << "  - OMEGA" << rptNewLine;
   *pMyPar<< symbol(QED) << "  - QED" << rptNewLine;
   *pMyPar<< symbol(INFINITY) << "  - INFINITY" << rptNewLine;
   *pMyPar<< symbol(DEGREES) << "  - DEGREES" << rptNewLine;
   *pMyPar<< symbol(OMICRON) << "  - OMICRON" << rptNewLine;
   *pMyPar<< symbol(PARTIAL) << "  - PARTIAL" << rptNewLine;
   *pMyPar<< symbol(DOT) << "  - DOT" << rptNewLine;
   *pMyPar<< symbol(DIAMOND) << "  - DIAMOND" << rptNewLine;
   *pMyPar<< symbol(FUNCTION) << "  - FUNCTION" << rptNewLine;
   *pMyPar<< symbol(PRODUCT) << "  - PRODUCT" << rptNewLine;
   *pMyPar<< symbol(SUM) << "  - SUM" << rptNewLine;
   *pMyPar<< symbol(INTEGRAL) << "  - INTEGRAL" << rptNewLine;
   *pMyPar<< symbol(ROOT) << "  - ROOT" << rptNewLine;
   *pMyPar<< symbol(TIMES) << "  - TIMES" << rptNewLine;
   *pMyPar<< symbol(DIVIDE) << "  - DIVIDE" << rptNewLine;
   *pMyPar<< symbol(LTE) << "  - LTE" << rptNewLine;
   *pMyPar<< symbol(GTE) << "  - GTE" << rptNewLine;
   *pMyPar<< symbol(NE) << "  - NE" << rptNewLine;
   *pMyPar<< symbol(EXACTLY) << "  - EXACTLY" << rptNewLine;
   *pMyPar<< symbol(PLUS_MINUS) << "  - PLUS_MINUS" << rptNewLine;
   *pMyPar<< symbol(ABOUT_EQUAL) << "  - ABOUT_EQUAL" << rptNewLine;
   *pMyPar<< symbol(APPROXIMATELY) << "  - APPROXIMATELY" << rptNewLine;
   *pMyPar<< symbol(ELLIPSES) << "  - ELLIPSES " << rptNewLine;
   *pMyPar<< symbol(VERTICAL_BAR) << "  - VERTICAL_BAR" << rptNewLine;
   *pMyPar<< symbol(HORIZONTAL_BAR) << "  - HORIZONTAL_BAR" << rptNewLine;
   *pMyPar<< symbol(ENTER) << "  - ENTER" << rptNewLine;
   *pMyPar<< symbol(EMPTY_SET) << "  - EMPTY_SET" << rptNewLine;
   *pMyPar<< symbol(REGISTER) << "  - REGISTER" << rptNewLine;
   *pMyPar<< symbol(COPYRIGHT) << "  - COPYRIGHT" << rptNewLine;
   *pMyPar<< symbol(TRADEMARK) << "  - TRADEMARK" << rptNewLine;
   *pMyPar<< symbol(LEFT_RIGHT_SINGLE_ARROW) << "  -LEFT_RIGHT_SINGLE_ARROW " << rptNewLine;
   *pMyPar<< symbol(LEFT_SINGLE_ARROW) << "  - LEFT_SINGLE_ARROW" << rptNewLine;
   *pMyPar<< symbol(UP_SINGLE_ARROW) << "  - UP_SINGLE_ARROW" << rptNewLine;
   *pMyPar<< symbol(RIGHT_SINGLE_ARROW) << "  - RIGHT_SINGLE_ARROW" << rptNewLine;
   *pMyPar<< symbol(DOWN_SINGLE_ARROW) << "  - DOWN_SINGLE_ARROW" << rptNewLine;
   *pMyPar<< symbol(LEFT_RIGHT_DOUBLE_ARROW) << "  -LEFT_RIGHT_DOUBLE_ARROW " << rptNewLine;
   *pMyPar<< symbol(LEFT_DOUBLE_ARROW) << "  - LEFT_DOUBLE_ARROW" << rptNewLine;
   *pMyPar<< symbol(UP_DOUBLE_ARROW) << "  - UP_DOUBLE_ARROW" << rptNewLine;
   *pMyPar<< symbol(RIGHT_DOUBLE_ARROW) << "  - RIGHT_DOUBLE_ARROW" << rptNewLine;
   *pMyPar<< symbol(DOWN_DOUBLE_ARROW) << "  - DOWN_DOUBLE_ARROW" << rptNewLine;


   //
   // Colors
   //
   *pMyPar<< rptNewLine << rptNewLine << "********** Color Stuff *********"<<rptNewLine;
   *pMyPar<< color(RED)  << " -red " << color(GREEN) << " -green" << rptNewLine;
   *pMyPar<< color(BLUE) << " -blue" << color(BLACK) << " -black" << rptNewLine;

   *p_chapter << pMyPar;

   // 
   // Styles
   //
   *pMyPar<< rptNewLine << rptNewLine << "********** Chapter Style Stuff *********"<<rptNewLine<<rptNewLine;

   // let's try out some new paragraphs with style
   rptParagraph* pMyPar02 = new  rptParagraph("Default");
   *pMyPar02<< "This is a default paragraph";
   *p_chapter << pMyPar02;

   rptParagraph* pMyPar1 = new  rptParagraph("Header1");
   *pMyPar1<< "This is a header1 paragraph";
   *p_chapter << pMyPar1;

   rptParagraph* pMyPar2 = new  rptParagraph("Header2");
   *pMyPar2<< "This is a header2 paragraph";
   *p_chapter << pMyPar2;

   rptParagraph* pMyPar3 = new  rptParagraph("Header3");
   *pMyPar3<< "This is a header3 paragraph";
   *p_chapter << pMyPar3;

   rptParagraph* pMyPar4 = new  rptParagraph("Header4");
   *pMyPar4<< "This is a header4 paragraph";
   *p_chapter << pMyPar4;

   rptParagraph* pMyPar5 = new  rptParagraph("Header5");
   *pMyPar5<< "This is a header5 paragraph";
   *p_chapter << pMyPar5;

   //
   // Tables
   //
   rptParagraph* pMyPar9 = new  rptParagraph();
   rptRcTable* pMyTable = new rptRcTable(5, 6.0);
   rptParagraph& caption = pMyTable->TableCaption();
   caption << "This is a test table";
   rptParagraph& label = pMyTable->TableLabel();
   label << "Table 1";

   pMyTable->SetTableHeaderStyle("ColumnHeader");
   pMyTable->SetColumnStyle(2,"ColumnNumber");

   *pMyPar9 << rptNewLine << "Let's Try Some Tables"<< rptNewLine;
   *pMyPar9 << pMyTable;
   *p_chapter << pMyPar9;

   // set column widths
   pMyTable->SetColumnWidth(0,0.5);
   pMyTable->SetColumnWidth(1,0.75);

   rptForceUnitTag   force_unit_tag(&unitMeasure::Newton);

   rptForceUnitValue force_proto(0.0,&unitMeasure::Newton,0,false); // don't show unit tag
   force_proto.SetFormat( sysNumericFormatTool::Engineering );
   force_proto.SetWidth( 15 );
   force_proto.SetPrecision(3);

   rptForceSectionValue sv_proto(0.0,&unitMeasure::Newton,0,false); // don't show unit tag
   sv_proto.SetFormat(sysNumericFormatTool::Engineering );

   rptRcInt     int_proto;

   // set up table header

   for (Int16 j=0; j<4; j++)
   {
      rptParagraph& ptemp = (*pMyTable)(0,j);
      ptemp << "Label" 
            << (Int16)(j+1);
      if (j > 1)
         ptemp << rptNewLine << force_unit_tag;
   }

   // fill up the table

   std::vector<double> doublevec;  // some vectors to store some data
   std::vector<long>   longvec;
   std::vector<std::string> stringvec;
   std::vector<sysSectionValue> sv_vec;

   // load up some bogus data
   for (j=0; j<20; j++)
   {
      longvec.push_back(j);
      doublevec.push_back(j*2000000.);
      stringvec.push_back("A string");
      sv_vec.push_back(sysSectionValue( 10*j,j/10 ) );
   }

   // send the data down to the table

   pMyTable->PutLongColumn(0, int_proto, longvec);
   pMyTable->PutStringColumn(1, stringvec);
   pMyTable->PutDoubleColumn(2, force_proto, doublevec);
   //ProtoReal.SetPrecision(6);
   pMyTable->PutSectionValueColumn(3, sv_proto, sv_vec);

   // put a hyperlink into the table
   rptParagraph& a_cell = (*pMyTable)(10,4);
   a_cell << new rptRcHyperTarget("The_Table") << new rptRcString("Link to Top", "The_Top");
    
   // put a image into the table
   rptParagraph& b_cell = (*pMyTable)(14,4);
   b_cell << new rptRcImage("f:\\wbfl\\wsdotlogo.gif","WSDOT Logo") << rptNewLine;
   b_cell.SetStyleName("ColumnCentered");


   // test the table copy constructor

   rptRcTable* pTableCopy = new rptRcTable(*pMyTable);
   pTableCopy->ClearParent();
   pTableCopy->SetCellPad(.060);
   pTableCopy->SetOutsideBorderStyle(rptRiStyle::SINGLE_THICK);
   pTableCopy->SetInsideBorderStyle(rptRiStyle::HAIR_THICK);

   *pMyPar9 << rptNewLine << rptNewLine << "A Table Copy With Some Changes" << rptNewLine << rptNewLine << pTableCopy;

   // put in a hypertarget for here and a hyperlink to the top
   rptParagraph* pMyPar11 = new  rptParagraph();
   *p_chapter << pMyPar11;
   *pMyPar11 << rptNewLine << rptNewLine<< new rptRcHyperTarget("The_Bottom");
   *pMyPar11 << new rptRcString("Link Back to the Top", "The_Top")<< rptNewLine;

   report << p_chapter;

   // some header and footer text
   rptPageLayout* pmy_layout = p_chapter->GetpPageLayout();
   pmy_layout->m_FooterParagraph << "Some Footer Text";
   pmy_layout->m_HeaderParagraph << "Some Header Text";

   //
   // Realize the report
   //
   std::ofstream ofile("c:\\temp\\test.htm");
   rptHtmlReportVisitor visitor( &ofile );
   visitor.VisitReport( &report );

   return 0;
}