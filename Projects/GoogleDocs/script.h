/* call
https://script.google.com/macros/s/AKfycbzLLZBfwAAm6qh1XuFL7cv101agoDb6v1ZIJyYwqy5OipTRFfM/exec?sheet=temp&value=10&date=01/01/2011%2011:22:10
*/

/*
var ss = SpreadsheetApp.openById('1vLJyJpFUk0Qatu2Rs6lgR62Cvwmu93xiNaMXHrK7Hw8');

function doGet(e)
{      
  if ( e !== undefined && e.parameter.value !== undefined && e.parameter.sheet !== undefined)
    {
      var sheet_str = e.parameter.sheet;
      var date = e.parameter.date; 
      var val = e.parameter.value;
      var sheet = ss.getSheetByName(sheet_str);   
      sheet.appendRow(['Cotton XL', date , '123']);
    }
 Logger.log(e.queryString);  
}

function create() 
{
  var ssNew = SpreadsheetApp.create("Temperatures", 10, 5);
  SpreadsheetApp.flush();
}

function addProduct() 
{
  var sheet = ss.getSheetByName('Temp');    
  sheet.appendRow(['Cotton XL', 'css004']);
}

function colors()
{
  SpreadsheetApp.setActiveSheet
  
  var sheet = SpreadsheetApp.getActiveSheet();
  for (var i = 0; i < 20; i++)
  {
    if ((i % 2) == 0) 
    {
      sheet.getRange('A1').setBackground('green');
      sheet.getRange('B1').setBackground('red');
    } else {
      sheet.getRange('A1').setBackground('red');
      sheet.getRange('B1').setBackground('green');
    }
    SpreadsheetApp.flush();
  }
}


*/
