///////////////////////////////////////////////////
// 
// RunRegression.js 
// A script for running PGSuper regression tests.
// Run with /? to get help.
//
//
///////////////////////////////////////////////////

// first some defaults
debugger;

var wsShell = new ActiveXObject("WScript.Shell");
var FSO = new ActiveXObject("Scripting.FileSystemObject");

var Logger = new ActiveXObject("WBFLLBAMTestFrame.FileTestLogger");
Logger.Open("OpenAndSave.log");


Run();

      
WScript.Quit(0);

// --------------------- functions ------------------

function Run () 
{
   // find all .xml files
   var f = FSO.GetFolder(".");
   var fc = new Enumerator(f.files);
   for (; !fc.atEnd(); fc.moveNext())
   {
     s = new String(fc.item());
     if (-1 != s.indexOf(".xml"))
     {
        var Tester = new ActiveXObject("WBFLLBAMTestFrame.LbamTester");
		var msg = "Opening : "+ s;
        DisplayMessage(msg);
		Logger.AddDescriptionEntry(msg);
		Tester.LoadFromFile(s);

        // Uncomment if results are to be recomputed and seeded in file
        DisplayMessage("Computing New Results");
        Tester.FillResults();

		var msg = "Saving : "+ s;
        DisplayMessage(msg);
		Logger.AddDescriptionEntry(msg);
		Tester.SaveToFile(s);
     }
   }
}


function DisplayMessage(msg)
{
   // could make this modal and add dialog-type messages for interactive mode
   WScript.Echo(msg);
}