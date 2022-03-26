const locations = [{ lat: 18.992064, lng: 72.834641 }];

let map;

function initMap() {
  map = new google.maps.Map(document.getElementById('map'), {
    center: locations[0],
    zoom: 8,
  });
  const marker = new google.maps.Marker({
    position: locations[0],
    map: map,
  });
}
