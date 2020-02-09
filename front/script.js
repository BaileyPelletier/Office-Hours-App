let vm = new Vue({
    el: "#app",
    data: {
	teacherData: [],
	visibleData: [],
	filterText: ""
    },
    created (){
	$.getJSON("http://35.245.72.191/app1", (data) => {
	    this.teacherData = data;
	    this.visibleData = this.teacherData;
	}).fail(() => {
	    $.getJSON("example.json", (data) => {
		this.teacherData = data;
		this.visibleData = this.teacherData;
	    });
	});
	
    },
    methods: {
	showModal(index) {
	    console.log("showModal with index: " + index);
	    $("#modal-" + index).modal('show');
	},
	closeModal(index) {
	    $("#modal-" + index).modal('hide');
	},
	filter() {
	    this.visibleData = this.teacherData.filter(t => {
		let lowName = t.name.toLowerCase();
		let lowFilter = this.filterText.toLowerCase();
		return lowName.includes(lowFilter);
	    });
	},
	buildMapsLink(place) {
	    let urlStem = "https://www.google.com/maps/search/?api=1&query=";
	    let placeEncoded = encodeURIComponent(place + ", UGA, Athens, GA");
	    //$("#maps-link-" + index).attr("href", urlStem + placeEncoded);
	    return urlStem + placeEncoded;
	}
    }
});
