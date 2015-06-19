difference() {
        
    union () {
        cylinder(2,33,33); //grundplatte
        translate ([0,0,2]) {
            cylinder (2,31,31); //abschlussplatte
        }
    }
        translate ([21,0,-0.5]) {
            cylinder(6,2,2);  //stangenloch
        }
        translate ([-21,0,-0.5]) {
            cylinder(6,2,2);  //stangenloch
        }
        translate ([0,25,-0.5]) {
            cylinder(6,4.5,4.5); //luftloch
        }
        translate ([0,-25,-0.5]) {
            cylinder(6,4.5,4.5);//luftloch
        }
        rotate (45,0,0) {
            translate ([0,-25,-0.5]) {
                cylinder(6,4.5,4.5);//luftloch
            }
            translate ([0,25,-0.5]) {
                cylinder(6,4.5,4.5);//luftloch
            }
        }
        rotate (-45,0,0) {
            translate ([0,-25,-0.5]) {
                cylinder(6,4.5,4.5);//luftloch
            }
            translate ([0,25,-0.5]) {
                cylinder(6,4.5,4.5);//luftloch
            }
        }
        translate([0,0,-0.5]){
            cylinder(6,5,5); //staubsensorloch
        }
    }
// bodenscheibe
    
