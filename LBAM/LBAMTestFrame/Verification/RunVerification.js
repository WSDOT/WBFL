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

// get down to business
InitTest();

var Logger = new ActiveXObject("WBFLLBAMTestFrame.FileTestLogger");
Logger.Open("Verify.log");

RunTest();

var CurrFolderSpec = ".";
var tests = Logger.TotalTests;
var fails = Logger.TotalFails;
DisplayMessage(tests + " Tests were run");

if (fails==0)
   DisplayMessage("Test Successful - no differences");
else
   DisplayMessage( fails + " TESTS FAILED!!!");

var st = fails!=0;
      
WScript.Quit(st);

// --------------------- functions ------------------

function RunTest () 
{
   // find all .pgs files and run pgsuper on them
   var f = FSO.GetFolder(".");
   var fc = new Enumerator(f.files);
   for (; !fc.atEnd(); fc.moveNext())
   {
     s = new String(fc.item());
     if (-1 != s.indexOf(".xml"))
     {
        var Tester = new ActiveXObject("WBFLLBAMTestFrame.LbamTester");
		var msg = "Running: "+ s;
        DisplayMessage(msg);
		Logger.AddDescriptionEntry(msg);
		var diff = Tester.ForceMinPercentDiff;
		Tester.LoadFromFile(s);
		Tester.ValidateResults( Logger );
     }
   }
}

function InitTest () 
{
   // clean up temporary files
   var f = FSO.GetFolder(".");
   var fc = new Enumerator(f.files);
   for (; !fc.atEnd(); fc.moveNext())
   {
     s = new String(fc.item());
     if (-1 != s.indexOf(".log") || -1 != s.indexOf(".tmp") || -1 != s.indexOf(".err"))
     {
        FSO.DeleteFile(s);
     }
   }
   
}

function DisplayMessage(msg)
{
   // could make this modal and add dialog-type messages for interactive mode
   WScript.Echo(msg);
}