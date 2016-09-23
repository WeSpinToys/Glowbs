function validateEntry(){
    var search = $('#navbarsearch').attr('value');
    var validEntry = (search.length < 0 || search.trim()=="") ? false : true;
    if(!validEntry) console.log('invalid search');
    return validEntry;
}