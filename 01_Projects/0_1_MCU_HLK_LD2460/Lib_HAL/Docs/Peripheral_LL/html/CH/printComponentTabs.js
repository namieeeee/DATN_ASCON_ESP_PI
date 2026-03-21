var strgURL = location.pathname; // path of current component

// constructor for the array of objects
function tabElement(id, folderName, tabTxt) {
    this.id = id; // elementID as needed in html; 
    this.folderName = folderName; // folder name of the component 
    this.tabTxt = tabTxt; // Text displayed as menu on the web
    this.currentListItem = '<li class="nav-item active" id="' + this.id + '" > <a class="nav-link" href="../../..' + this.folderName + 'index.html">' + this.tabTxt + '<span class="sr-only">(current)</span></a></li>';
    this.listItem = '<li class="nav-item" id="' + this.id + '"> <a class="nav-link" href="../../..' + this.folderName + 'index.html"><span>' + this.tabTxt + '</span></a></li>';
};

// array of objects
var arr = [];

// fill array
arr.push(new tabElement("GENERAL", "/General/html/CH/", "General"));
arr.push(new tabElement("BOARD", "/Board/html/CH/", "Board"));
arr.push(new tabElement("PERIPHERAL", "/Peripheral/html/CH/", "Peripheral"));
arr.push(new tabElement("PERIPHERAL_LL", "/Peripheral_LL/html/CH/", "Peripheral (LL)"));
arr.push(new tabElement("MIDDLEWARE", "/Middleware/html/CH/", "Middleware"));
//arr.push(new tabElement("APPLICATION", "/Application/html/CH/", "Application"));
arr.push(new tabElement("Q&A", "/QA/html/CH/", "Q&A"));


// write tabs
// called from the header file.
function writeComponentTabs() {
    for (var i = 0; i < arr.length; i++) {
        if (strgURL.search(arr[i].folderName) > 0) { // if this is the current folder
            document.write(arr[i].currentListItem); // then print and highlight the tab
        } else {
            document.write(arr[i].listItem); // else, print the tab
        }
    }
};