var httpRequest = new XMLHttpRequest();

function paginate(pages_requested, filters) {
    var page = 1;
    var overall = 0;

    function alertContents() {
        if (httpRequest.readyState === 4) {
          if (httpRequest.status === 200) {
            var text = JSON.parse(httpRequest.responseText);
            var faves = listFavorites();
            var results = [];
            var space = "";
            for (var i = 0; i < text.length; i++){
                if (overall+i < 10){
                    space="   ";
                } else if (overall+i < 100) {
                    space = "  ";
                } else {
                    space = " ";
                }

                if (filters.length > 0) {
                    var files = Object.keys(text[i].files);
                    for (var j = 0; j < files.length; j++){
                        console.log(text[i].files[files[j]].language);
                        if (filters.indexOf(text[i].files[files[j]].language) != -1 && faves.indexOf(text[i].html_url) === -1){
                            results.push("<a href=\"" + text[i].html_url + "\"> gist" + space + (overall+i) + "-->" + text[i].description + "</a><br>");
                            break;
                        }
                    }
                    
                } else if (faves.indexOf(text[i].html_url) === -1) {
                    results.push("<a href=\"" + text[i].html_url + "\"> gist" + space + (overall+i) + "-->" + text[i].description + "</a><br>");
                }

            }
        } else {
            alert('There was a problem with the request.');
            }
            saveLocalStorage(results);
            displayLocalStorage('id'+page);
        }
    }

    function getGistList() {
        if(!httpRequest){
            throw 'Unable to create httpRequest';
        }
        
        httpRequest.onreadystatechange = alertContents;
        httpRequest.open('GET', 'https://api.github.com/gists/public?page='+ page + '&per_page=30', false);
        httpRequest.send(null);
    }

    while (page <= pages_requested){
        getGistList();
        page += 1;
        overall += 30;
    }
}

window.onload = function() {
    document.getElementById('id1').innerHTML = "Optional, enter desired number of pages of results.<br>Optional, pick filters.<br>Or, just click search!";
    document.getElementById('favorites').innerHTML = "Pick up to 5 favorites, paste their URLs below."
    //getGistList();
}

function displayLocalStorage(id) {
    var storedList = JSON.parse(localStorage.getItem('json_store'));
    var htmlstring = "";
    for (var i = 0; i < storedList.length; i++){
        htmlstring += storedList[i];
    }
    document.getElementById(id).innerHTML = htmlstring;
}

function displayFavorites() {
    var storedList = JSON.parse(localStorage.getItem('fav_store'));
    var htmlstring = "";
    for (var i = 0; i < storedList.length; i++){
        htmlstring += "favorite " + (i+1) + ". "
        htmlstring += "<a href=\"" + storedList[i] + "\">";
        htmlstring += storedList[i] + "</a>";
        htmlstring += "<br>";
    }
    document.getElementById('favorites').innerHTML = htmlstring;
}

function listFavorites() {
    return JSON.parse(localStorage.getItem('fav_store'));
}

function saveLocalStorage(items) {
    localStorage.setItem('json_store', JSON.stringify(items));
}

function saveFavorites(faves) {
    localStorage.setItem('fav_store', JSON.stringify(faves));
}

function clearLocalStorage() {
    localStorage.clear();
}

function searchTheThings(){
    //grab the number of pages they want
    var sc = parseInt(document.getElementsByName('searchcount')[0].value, 10);
    var cb = document.getElementsByName('filter');
    var filters = [];
    for (var i = 0; i < cb.length; i++){
        if (cb[i].checked){
            filters.push(cb[i].id);
        }
    }
    //throw away anything that isn't a number from 1 to 5
    if (isNaN(sc) || (sc > 5) || (sc < 1)) {
        sc = 1;
    }
    saveTheFaves();
    paginate(sc, filters);
    console.log(cb, filters);//debug

}

function saveTheFaves(){
    var tb = document.getElementsByName('favorite');
    var favorites = [];
    for (var i = 0; i < tb.length; i++){
        favorites.push(tb[i].value);
    }
    saveFavorites(favorites);
    displayFavorites();
}