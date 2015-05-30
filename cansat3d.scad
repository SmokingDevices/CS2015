difference() {
        cylinder(2,33,33);
        translate ([21,0,-0.5]) {
            cylinder(3,3,3);  //loch
        }
        translate ([-21,0,-0.5]) {
            cylinder(3,3,3);  //loch
        }
        translate ([0,25,-0.5]) {
            cylinder(3,4.5,4.5);
        }
        translate ([0,-25,-0.5]) {
            cylinder(3,4.5,4.5);
        }
        rotate (45,0,0) {
            translate ([0,-25,-0.5]) {
                cylinder(3,4.5,4.5);
            }
            translate ([0,25,-0.5]) {
                cylinder(3,4.5,4.5);
            }
        }
        rotate (-45,0,0) {
            translate ([0,-25,-0.5]) {
                cylinder(3,4.5,4.5);
            }
            translate ([0,25,-0.5]) {
                cylinder(3,4.5,4.5);
            }
        }
    }
// bodenscheibe
    
translate([0,0,115]) {
    difference() {
        cylinder(2,33,33);
        translate ([21,0,0]) {
            cylinder(3,3,3); //loch
        }
        translate ([-21,0,0]) {
            cylinder(3,3,3); //loch
        }
        translate([0,0,1]) {
            cylinder (3,5,5);
        }
        translate ([0,-15,1]) {
            cylinder (3,2,2);
        }
        rotate (22.5,0,0) {
            translate ([0,26,1]) {
                cylinder (3,1,1);
            }
            translate ([0,29,1]) {
                cylinder (3,1,1);
            }
        }
        rotate (67.5,0,0) {
            translate ([0,26,1]) {
                cylinder (3,1,1);//schnurloch a
        }
            translate ([0,29,1]) {
                cylinder (3,1,1); //schnurloch b
        }
        }
        rotate (157.5,0,0) {
            translate ([0,26,1]) {
                cylinder (3,1,1);//schnurloch a
        }
            translate ([0,29,1]) {
                cylinder (3,1,1); //schnurloch b
        }
        }
        rotate (-67.5,0,0) {
            translate ([0,26,1]) {
                cylinder (3,1,1);//schnurloch a
        }
            translate ([0,29,1]) {
                cylinder (3,1,1); //schnurloch b
        }
        }
        rotate (-22.5,0,0) {
            translate ([0,26,1]) {
                cylinder (3,1,1);//schnurloch a
        }
            translate ([0,29,1]) {
                cylinder (3,1,1); //schnurloch b
        }
        }
        rotate (202.5,0,0) {
            translate ([0,26,1]) {
                cylinder (3,1,1);//schnurloch a
        }
            translate ([0,29,1]) {
                cylinder (3,1,1); //schnurloch b
        }
        }
        rotate (112.5,0,0) {
            translate ([0,26,1]) {
                cylinder (3,1,1);//schnurloch a
        }
            translate ([0,29,1]) {
                cylinder (3,1,1); //schnurloch b
        }
        }
        rotate (-112.5,0,0) {
            translate ([0,26,1]) {
                cylinder (3,1,1);//schnurloch a
        }
            translate ([0,29,1]) {
                cylinder (3,1,1); //schnurloch b
        }
        }
    }
}
//deckscheibe

translate([21,0,1]) {
    cylinder (115,3,3);
}
translate ([-21,0,1]) {
    cylinder (115,3,3);
}
//stangen

rotate (45,0,0) {
   translate ([0,0,109]) {
    difference() {
        cube ([49,49,10],true);//platine
        rotate (-45,0,0) {
            translate([0,38,0]) {
                cube ([18,18,19],true);//ecke(y)
            }
            translate ([0,-38,0]) {
                cube ([18,18,19],true); //ecke(-y)
            }
            translate ([38,0,0,]) {
                cube ([18,18,19],true);//ecke (x)
            }
            translate ([-38,0,0]) {
                cube ([18,18,19],true);//ecke(-x)
            }
        }
    }
} //gps
translate ([0,0,98]) {
    difference() {
        cube ([49,49,10],true);//platine
        rotate (-45,0,0) {
            translate([0,38,0]) {
                cube ([18,18,19],true);//ecke(y)
            }
            translate ([0,-38,0]) {
                cube ([18,18,19],true); //ecke(-y)
            }
            translate ([38,0,0,]) {
                cube ([18,18,19],true);//ecke (x)
            }
            translate ([-38,0,0]) {
                cube ([18,18,19],true);//ecke(-x)
            }
        }
    }
}//temperatur
translate ([0,0,83]) {
    difference() {
            cube ([49,49,2],true);//platine
        rotate (-45,0,0) {
            translate([0,38,0]) {
                cube ([18,18,11],true);//ecke(y)
            }
            translate ([0,-38,0]) {
                cube ([18,18,11],true); //ecke(-y)
            }
            translate ([38,0,0,]) {
                cube ([18,18,11],true);//ecke (x)
            }
            translate ([-38,0,0]) {
                cube ([18,18,11],true);//ecke(-x)
            }
        }
    }
    translate([0,20,5])  {
    cube ([26,5,8],true); //pinleiste(y)
    }
    translate([0,-20,5])  {
    cube ([26,5,8],true); //pinleiste(-y)
    }
    translate([20,0,5])  {
    cube ([5,26,8],true); //pinleiste(x)
    }
    translate([0,0,2]) {
    cube ([34,34,2],true); //besetzter platz
    }
    translate([-23,11,0]) {
        cube ([5,5,8]); //stromanschluss-plastik-dingens
    }
}//computer(processor)
translate ([0,0,72]) {
    difference() {
            cube ([49,49,2],true);//platine
        rotate (-45,0,0) {
            translate([0,38,0]) {
                cube ([18,18,11],true);//ecke(y)
            }
            translate ([0,-38,0]) {
                cube ([18,18,11],true); //ecke(-y)
            }
            translate ([38,0,0,]) {
                cube ([18,18,11],true);//ecke (x)
            }
            translate ([-38,0,0]) {
                cube ([18,18,11],true);//ecke(-x)
            }
        }
    }
    translate([0,20,5])  {
    cube ([26,5,8],true); //pinleiste(y)
    }
    translate([0,-20,5])  {
    cube ([26,5,8],true); //pinleiste(-y)
    }
    translate([20,0,5])  {
    cube ([5,26,8],true); //pinleiste(x)
    }
    translate([0,0,2]) {
    cube ([34,34,5],true); //besetzter platz
    }
}//SDkarte
translate ([0,0,61]) {
    difference() {
            cube ([49,49,2],true);//platine
        rotate (-45,0,0) {
            translate([0,38,0]) {
                cube ([18,18,11],true);//ecke(y)
            }
            translate ([0,-38,0]) {
                cube ([18,18,11],true); //ecke(-y)
            }
            translate ([38,0,0,]) {
                cube ([18,18,11],true);//ecke (x)
            }
            translate ([-38,0,0]) {
                cube ([18,18,11],true);//ecke(-x)
            }
        }
    }
    translate([0,20,5])  {
    cube ([26,5,8],true); //pinleiste(y)
    }
    translate([0,-20,5])  {
    cube ([26,5,8],true); //pinleiste(-y)
    }
    translate([20,0,5])  {
    cube ([5,26,8],true); //pinleiste(x)
    }
    translate([0,0,2]) {
    cube ([34,34,2],true); //besetzter platz
    }
}//sender
//platinen

translate ([0,0,11]) {
    rotate (60,0,0) {
        difference() {
            cube([46,34,18],true);
            cylinder (18,4,8);
        }
    }
}
//staubsensor


rotate(-110,0,0) {
translate([-3,28,23]) {
     cube([18,1,42],true); //platine
    translate([0,4,9]) {
        cube ([8,8,8],true);//kamera-linse
    }
    translate ([-6,-8.5,-6]) {
        cube ([15,8,27]);//akku
    }
}
}//kamera

translate ([-6,-2.5,65.75]) {
    cube ([41,30,3],true);//lipo-akku1
}
translate ([-6,-2.5,79]) {
    cube ([41,30,3],true);//lipo-akku2
}
translate ([-6,-2.5,69.25]) {
    cube ([41,30,3],true);//lipo-akku3
}
translate ([-6,-2.5,91]) {
    cube ([41,30,3],true);//lipo-akku4
}
//akkus
}


rotate(-60,0,0) {
    translate ([0,0,0]) {
        difference () {
            cylinder (115,33,33); //aussenhuelle
            translate ([0,0,-0.5]) {
                cylinder (116,31,31);//hohlraum
            translate ([0,30,32]) {
                cube ([12,10,10],true);//guckloch kamera
            }
        }
        }
    }
}
//huelle


translate([0,0,300]) {
    difference () {
        sphere (180);//fallschirm aussen
        translate ([0,0,0]) {
            sphere(179);//fallschirm aushuellen
        }
        translate([0,0,-90]) {
            cube ([600,600,200],true);//fallshirm halbieren
        }
    }
    translate([0,0,-90]) {
        cylinder(100,0,180);//gase
    }
    translate ([0,0,-150]) {
        cylinder (65,1.5,1.5);//schnur
    }
    translate([0,0,-160]) {
        cylinder (15,2.5,2.5);//schaft
    }
    difference() {
        translate([0,0,-160]) {
            cylinder (3,12.5,12.5);//ringscheibe
        }
        rotate(0,0,0) {    
            translate([0,10,-160]) {
                    cylinder (5, 1.5,1.5);//loch
            }
        }
        rotate(45,0,0) {    
            translate([0,10,-160]) {
                    cylinder (5, 1.5,1.5);//loch
            }
        }
        rotate(90,0,0) {    
            translate([0,10,-160]) {
                    cylinder (5, 1.5,1.5);//loch
            }
        }
        rotate(135,0,0) {    
            translate([0,10,-160]) {
                    cylinder (5, 1.5,1.5);//loch
            }
        }
        rotate(-45,0,0) {    
            translate([0,10,-160]) {
                    cylinder (5, 1.5,1.5);//loch
            }
        }
        rotate(-90,0,0) {    
            translate([0,10,-160]) {
                    cylinder (5, 1.5,1.5);//loch
            }
        }
        rotate(-135,0,0) {    
            translate([0,10,-160]) {
                    cylinder (5, 1.5,1.5);//loch
            }
        }
        rotate(180,0,0) {    
            translate([0,10,-160]) {
                    cylinder (5, 1.5,1.5);//loch
            }
        }
    }
}

//fallschirm
/*
rotate (a=45,v=(0,0,0)) {
    translate([20,90,30]) {
        cube([2,2,50]);
    }
}



/*
//TESTS:

translate ([80,0,1]) {
    difference() {
            cube ([49,49,2],true);//platine
        rotate (-45,0,0) {
            translate([0,38,0]) {
                cube ([18,18,11],true);//ecke(y)
            }
            translate ([0,-38,0]) {
                cube ([18,18,11],true); //ecke(-y)
            }
            translate ([38,0,0,]) {
                cube ([18,18,11],true);//ecke (x)
            }
            translate ([-38,0,0]) {
                cube ([18,18,11],true);//ecke(-x)
            }
        }
    }
    translate([0,20,5])  {
    cube ([26,5,8],true); //pinleiste(y)
    }
    translate([0,-20,5])  {
    cube ([26,5,8],true); //pinleiste(-y)
    }
    translate([20,0,5])  {
    cube ([5,26,8],true); //pinleiste(x)
    }
    translate([0,0,2]) {
    cube ([34,34,2],true); //besetzter platz
    }
}
//testplatine



translate ([-20,90,21]) {
    cube([18,1,42],true); //platine
    translate([0,4,9]) {
        cube ([8,8,8],true);//kamera-linse
    }
    translate ([-6,-8.5,-6]) {
        cube ([15,8,27]);//akku
    }
}//testkamera


translate ([-90,30,0]) {
    cube ([41,30,3]);//lipo-akku
}//testakku

