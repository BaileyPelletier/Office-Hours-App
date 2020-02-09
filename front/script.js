let vm = new Vue({
    el: "#app",
    data: {
	teacherData: []
    },
    created (){
	$.getJSON("example.json", (data) => {
	    this.teacherData = data;
	});	  
    },
    methods: {
	showData(teacher) {
	    console.dir(teacher);
	    $("#modal-" + teacher.name).modal('show');
	}
    }
});
