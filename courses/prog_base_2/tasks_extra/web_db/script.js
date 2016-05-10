function create(){
  var editBox = document.getElementById('edit_form_box');
  if (editBox.style.getPropertyValue("visibility") == "hidden"){
    editBox.style.visibility="visible";
  }
  var editForm = document.getElementById('edit_form');
  editForm.action="/new";
  var submitBtn = document.getElementById('submit_btn');
  submitBtn.value="Insert";
  var formHeaderText = document.getElementById('form_header_text');
  formHeaderText.textContent="Insert new record:";
  var columnsNum = document.getElementById('columns_num').textContent;
  for (var i = 0; i < columnsNum; i++){
    var inId = "input#"+i;
    var curInput = document.getElementById(inId);
    curInput.value="";
    if (i == 0){
      curInput.readOnly = false;
      var lastId = document.getElementById('last_id').textContent;
      curInput.value = parseInt(lastId) + 1;
    }
  }

}

function edit(id){
  var editBox = document.getElementById('edit_form_box');
  if (editBox.style.getPropertyValue("visibility") == "hidden"){
    editBox.style.visibility="visible";
  }
  var editForm = document.getElementById('edit_form');
  editForm.action="/update";
  var submitBtn = document.getElementById('submit_btn');
  submitBtn.value="Update";
  var formHeaderText = document.getElementById('form_header_text');
  formHeaderText.textContent="Edit this record: ";
  var columnsNum = document.getElementById('columns_num').textContent;
  for (var i = 0; i < columnsNum; i++){
    var inId = "input#"+i;
    var curInput = document.getElementById(inId);
    if (i==0) curInput.readOnly = true;
    var sourceId = id+"_field#"+i;
    var curSource = document.getElementById(sourceId).textContent;
    curInput.value = curSource;
  }
}
