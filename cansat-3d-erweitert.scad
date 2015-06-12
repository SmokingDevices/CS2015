//beware of easter eggs ;)
translate([0,80,0]) {
difference() {
        
    union () {
        cylinder(2,33,33); //grundplatte
        translate ([0,0,2]) {
            cylinder (2,31,31); //abschlussplatte
        }
    }
    translate([4,5,-1]) {
        cylinder(10,7.5,7.5);
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
    }
}
//bodenscheibe cansat-alt




difference() {
        
    union () {
        cylinder(2,33,33); //grundplatte
        translate ([0,0,2]) {
            cylinder (2,31,31); //abschlussplatte
        }
    }
        translate ([21,0,-0.5]) {
            cylinder(6,1.5,1.5);  //stangenloch
        }
        translate ([-21,0,-0.5]) {
            cylinder(6,1.5,1.5);  //stangenloch
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
    }
// bodenscheibe
    
translate([0,0,115]) {
    difference() {
        union() {
            cylinder(2,33,33);
            translate ([0,0,-2]) {
            cylinder (2,31,31); //abschlussplatte
        }
        }
         translate([0,12,0]) {
            cube ([6,7,5],true);//schalterloch
        }
        translate ([21,0,-3]) {
            cylinder(6,1.5,1.5); //stangenloch
        }
       
        translate ([-21,0,-3]) {
            cylinder(6,1.5,1.5); //stangenloch
        }
        translate([0,0,-2.5]) {
            cylinder (6,5,5); //luftloch
        }
        translate ([0,-13,-3]) {
            cylinder (6,2,2); //NTCloch
        }
        rotate (22.5,0,0) {
           translate ([0,22,-3]) {
                cylinder (6,2,2);//schnurloch a
        }
            translate ([0,28,-3]) {
                cylinder (6,2,2); //schnurloch b
        }
        }
        rotate (67.5,0,0) {
           translate ([0,22,-3]) {
                cylinder (6,2,2);//schnurloch a
        }
            translate ([0,28,-3]) {
                cylinder (6,2,2); //schnurloch b
        }
        }
        rotate (157.5,0,0) {
         translate ([0,22,-3]) {
                cylinder (6,2,2);//schnurloch a
        }
            translate ([0,28,-3]) {
                cylinder (6,2,2); //schnurloch b
        }
        }
        rotate (-67.5,0,0) {
          translate ([0,22,-3]) {
                cylinder (6,2,2);//schnurloch a
        }
            translate ([0,28,-3]) {
                cylinder (6,2,2); //schnurloch b
        }
        }
        rotate (-22.5,0,0) {
         translate ([0,22,-3]) {
                cylinder (6,2,2);//schnurloch a
        }
            translate ([0,28,-3]) {
                cylinder (6,2,2); //schnurloch b
        }
        }
        rotate (202.5,0,0) {
         translate ([0,22,-3]) {
                cylinder (6,2,2);//schnurloch a
        }
            translate ([0,28,-3]) {
                cylinder (6,2,2); //schnurloch b
        }
        }
        rotate (112.5,0,0) {
          translate ([0,22,-3]) {
                cylinder (6,2,2);//schnurloch a
        }
            translate ([0,28,-3]) {
                cylinder (6,2,2); //schnurloch b
        }
        }
        rotate (-112.5,0,0) {
          translate ([0,22,-3]) {
                cylinder (6,2,2);//schnurloch a
        }
            translate ([0,28,-3]) {
                cylinder (6,2,2); //schnurloch b
        }
        }
    }
}
//deckscheibe

translate([21,0,1]) {
    cylinder (115,1.5,1.5);
}
translate ([-21,0,1]) {
    cylinder (115,1.5,1.5);
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
        translate([0,0,-190]) {
            cube ([700,700,400],true);//fallshirm halbieren
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



difference () {
    translate ([0,0,117]) {
        cylinder (23,33,12.5); //"schnüre"
    }
    translate ([0,0,117]) {
        cylinder (23,32,11.5); 
    }
}


/*
//hm...scheinbar wurde da jemandem langweilig...ob hier vielleicht noch irgendwo ein easter egg versteckt ist?    ...so als belohnung dass man sich den ganzen code durchliest?  :/

translate ([0,100,0]) {
    cube ([80,10,10]);
    translate([0,50,0]) {
        cube ([80,10,10]);
    }
    rotate([0,0,45]) {
       translate([0,00,0]) {
        cube ([80,10,10]);
    } 
    }
    translate([0,100,0]) {
        cube ([80,10,10]);
    }
    translate([0,150,0]) {
        cube ([80,10,10]);
    }
    translate([0,100,0]) {
        cube ([10,50,10]);
    }
    translate([70,100,0]) {
        cube ([10,50,10]);
    }
    translate([120,100,0]) {
        cube ([90,10,10]);
    }
    translate([120,150,0]) {
        cube ([50,10,10]);
    }
    translate([120,100,0]) {
        cube ([10,50,10]);
    }
    translate([170,110,0]) {
        cube ([10,50,10]);
    }
    translate([170,50,0]) {
        cube ([10,20,10]);
    }
    translate([120,50,0]) {
        cube ([10,20,10]);
    }
}

//:D
















/*
//TESTS:



rotate([-15,40,0]) {
    translate ([-95,-29,63]) {
        cylinder (38,1.5,1.5);//canschnur
    }
    rotate([0,0,44]) {
       translate ([-95,-29,63]) {
        cylinder (38,1.5,1.5);//canschnur
    } 
    }
   
}

//schnüre am cansat sind echt müselig darum oben nur der einfache zylinder als veranschaulichung; gezeichnet: angehende amateur grafikerin :P





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


difference() {
    union () {
        translate ([0,80,0]) {
            cylinder(2,33,33);
        }
        translate ([0,80,2]) {
            cylinder (2,31,31);
        }
    }
    translate([0,80,-1]) {   
    cylinder (6,5,5);
    }
}
//testplatte mit doppelboden

