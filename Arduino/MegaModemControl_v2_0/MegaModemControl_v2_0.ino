#include <LiquidCrystal.h>
#include <Flash.h>

//IP address and port of the remote server
String IPaddress = "176.250.20.57";
String port = "6100";

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

String receivedString = "";

FLASH_STRING(fullString, 
                  "[SK310413:80[0003:258,0002:263,0000:283,0005:307,0003:322,0004:346,0003:349,0252:361,0511:375,1032:391,"
                  "2091:391,4193:396,5207:374,6225:350,5214:328,4211:321,2133:308,1079:305,0558:289,0288:284,0003:281,0003"
                  ":252,0004:229,0005:203][SK01LI19005:04:0413:0204132154:142:0[(0105130000:456:079:033:281)(0105130845:40"
                  "4:033:002:263)(0105131702:010:002:001:263)(0105131857:069:001:000:278)]][SK02PB12008:04:0844:0204131650"
                  ":504:1[(0105130000:329:081:056:288)(0105130703:472:056:016:282)(0105131620:439:016:000:265)(0205131035:"
                  "016:100:099:264)]][SK03LI19005:04:0511:0104132255:238:0[(0105130000:345:067:042:270)(0105130710:392:042"
                  ":012:283)(0105131515:221:012:000:264)(0205130532:411:100:066:279)]][SK04PB12008:04:0448:0204132233:591:"
                  "1[(0105130000:471:084:037:279)(0105130911:105:037:027:277)(0105131225:227:027:011:260)(0105131748:295:0"
                  "11:000:276)]][SK05PB12008:04:0048:0204131719:458:0[(0105130000:172:051:034:277)(0105130437:282:034:010:"
                  "264)(0105131015:335:010:000:286)(0205130340:158:100:089:282)]][SK06LI19005:04:1414:0204131732:252:1[(01"
                  "05130000:375:059:025:270)(0105130740:256:025:005:271)(0105131328:212:005:000:264)(0205130405:169:100:08"
                  "5:270)]][SK07PB12008:04:1131:0104131858:122:0[(0105130000:224:053:037:279)(0105130505:399:037:004:276)("
                  "0105131341:192:004:000:272)(0205130223:044:100:096:265)]][SK08PB12008:04:0735:0204131254:362:0[(0105130"
                  "000:477:079:039:287)(0105130955:245:039:019:280)(0105131452:049:019:015:281)(0105131737:233:015:000:265"
                  ")]][SK09PB12008:04:0487:0204131158:500:1[(0105130000:447:095:063:273)(0105130926:497:063:018:279)(01051"
                  "31845:350:018:000:279)(0205131131:492:100:055:263)]][SK10PB12008:04:1019:0104131958:183:0[(0105130000:2"
                  "17:087:070:284)(0105130520:048:070:066:275)(0105130805:019:066:065:268)(0105130957:072:065:059:267)]][S"
                  "K11LI19005:04:0692:0204131637:342:1[(0105130000:256:078:057:280)(0105130525:289:057:034:266)(0105131211"
                  ":043:034:031:262)(0105131353:019:031:029:263)]][SK12LI19005:04:0678:0204131349:691:1[(0105130000:139:05"
                  "6:043:260)(0105130336:493:043:005:278)(0105131245:027:005:003:285)(0105131500:186:003:000:271)]][SK13LI"
                  "19005:04:0335:0104131816:336:0[(0105130000:305:088:058:271)(0105130647:220:058:039:289)(0105131128:194:"
                  "039:020:267)(0105131600:026:020:017:286)]][SK14PB12008:04:0485:0104132046:519:1[(0105130000:147:073:062"
                  ":276)(0105130351:430:062:029:279)(0105131158:461:029:000:285)(0205130700:290:100:076:262)]][SK15PB12008"
                  ":04:0287:0104131821:473:1[(0105130000:253:063:038:262)(0105130543:282:038:016:268)(0105131211:070:016:0"
                  "10:288)(0105131503:297:010:000:277)]][SK16LI19005:04:0231:0204131850:376:1[(0105130000:243:056:036:273)"
                  "(0105130542:180:036:022:281)(0105131011:099:022:013:260)(0105131242:422:013:000:285)]][SK17LI19005:04:1"
                  "614:0204131219:673:0[(0105130000:288:058:029:275)(0105130548:022:029:028:277)(0105130736:485:028:000:26"
                  "1)(0205130315:158:100:086:284)]][SK18LI19005:04:1274:0204131150:501:1[(0105130000:229:088:067:279)(0105"
                  "130502:409:067:033:265)(0105131258:392:033:000:264)(0105132105:031:000:000:271)]][SK19LI19005:04:1804:0"
                  "104131837:666:1[(0105130000:106:076:066:265)(0105130337:020:066:065:269)(0105130531:232:065:048:259)(01"
                  "05131117:229:048:031:279)]][SK20PB12008:04:0634:0104131032:685:0[(0105130000:104:063:054:265)(010513032"
                  "7:240:054:032:268)(0105130919:047:032:027:275)(0105131158:329:027:000:281)]][SK21LI19005:04:0979:010413"
                  "1618:629:1[(0105130000:206:077:060:268)(0105130505:147:060:049:278)(0105130834:139:049:038:277)(0105131"
                  "246:315:038:009:260)]][SK22PB12008:04:0398:0204131755:335:0[(0105130000:202:062:045:269)(0105130422:294"
                  ":045:018:259)(0105131059:053:018:014:284)(0105131323:261:014:000:274)]][SK23LI19005:04:0399:0204131320:"
                  "078:0[(0105130000:359:075:047:265)(0105130723:499:047:000:287)(0205130350:213:100:084:286)(0205130902:0"
                  "59:084:078:268)]][SK24LI19005:04:1159:0104131434:260:1[(0105130000:388:099:067:287)(0105130749:416:067:"
                  "035:279)(0105131545:012:035:034:260)(0105131657:460:034:000:261)]][SK25PB12008:04:0687:0104131856:192:0"
                  "[(0105130000:052:064:060:287)(0105130249:201:060:045:264)(0105130727:379:045:018:278)(0105131456:268:01"
                  "8:000:273)]][SK26LI19005:04:1718:0104131354:087:1[(0105130000:396:065:025:282)(0105130728:011:025:024:2"
                  "69)(0105130932:053:024:019:260)(0105131157:057:019:014:266)]][SK27PB12008:04:0470:0104131723:093:1[(010"
                  "5130000:389:076:046:285)(0105130819:468:046:007:268)(0105131754:291:007:000:280)(0205130947:380:100:071"
                  ":285)]][SK28LI19005:04:1818:0104131420:125:1[(0105130000:023:094:092:265)(0105130143:125:092:082:264)(0"
                  "105130518:231:082:063:277)(0105131020:207:063:044:261)]][SK29LI19005:04:0559:0104131052:624:0[(01051300"
                  "00:424:065:023:274)(0105130814:426:023:000:259)(0205130142:498:100:055:274)(0205131055:404:055:026:276)"
                  "]][SK30PB12008:04:0991:0204132123:487:0[(0105130000:213:099:083:272)(0105130506:284:083:059:268)(010513"
                  "1115:482:059:015:289)(0105132058:274:015:000:283)]][SK31LI19005:04:0647:0104132032:177:1[(0105130000:31"
                  "9:085:060:280)(0105130629:290:060:031:260)(0105131256:193:031:014:271)(0105131735:130:014:002:275)]][SK"
                  "32LI19005:04:1568:0204132239:529:0[(0105130000:460:052:017:265)(0105130851:095:017:009:278)(0105131128:"
                  "420:009:000:284)(0205130618:098:100:091:273)]][SK33PB12008:04:0094:0204131134:409:0[(0105130000:253:051"
                  ":026:261)(0105130515:134:026:015:262)(0105130901:488:015:000:287)(0205130421:298:100:075:287)]][SK34LI1"
                  "9005:04:0847:0204131839:518:1[(0105130000:263:060:040:281)(0105130612:351:040:005:262)(0105131357:445:0"
                  "05:000:279)(0205130855:215:100:082:273)]][SK35PB12008:04:0437:0104131814:329:1[(0105130000:028:069:066:"
                  "279)(0105130127:368:066:038:263)(0105130915:257:038:017:263)(0105131427:192:017:000:277)]][SK36LI19005:"
                  "04:1560:0104131151:637:1[(0105130000:492:083:045:287)(0105131008:379:045:007:281)(0105131816:035:007:00"
                  "5:266)(0105131959:086:005:000:271)]][SK37PB12008:04:0202:0204131352:383:0[(0105130000:060:075:071:273)("
                  "0105130216:214:071:051:285)(0105130725:055:051:047:267)(0105131007:240:047:025:288)]][SK38PB12008:04:02"
                  "26:0204131211:662:1[(0105130000:446:074:040:267)(0105130819:401:040:000:278)(0205130211:123:100:089:289"
                  ")(0205130520:296:089:059:263)]][SK39LI19005:04:0503:0104131734:475:1[(0105130000:405:097:066:269)(01051"
                  "30756:280:066:044:276)(0105131340:470:044:008:285)(0105132224:402:008:000:284)]][SK40PB12008:04:0650:01"
                  "04132057:563:0[(0105130000:296:070:045:274)(0105130607:446:045:008:275)(0105131503:426:008:000:281)(020"
                  "5130950:370:100:066:263)]][SK41PB12008:04:0167:0104131447:130:1[(0105130000:406:092:055:276)(0105130833"
                  ":069:055:049:282)(0105131041:248:049:025:259)(0105131644:162:025:008:261)]][SK42PB12008:04:0601:0204132"
                  "345:428:0[(0105130000:128:070:061:259)(0105130300:078:061:055:273)(0105130547:446:055:010:272)(01051315"
                  "00:314:010:000:266)]][SK43LI19005:04:1443:0204131344:292:1[(0105130000:332:069:041:286)(0105130732:379:"
                  "041:003:272)(0105131542:213:003:000:282)(0205130833:021:100:098:263)]][SK44PB12008:04:0459:0204131831:4"
                  "94:0[(0105130000:204:093:076:263)(0105130423:415:076:038:273)(0105131317:474:038:004:276)(0105132311:48"
                  "4:004:000:270)]][SK45PB12008:04:0394:0204132035:316:0[(0105130000:285:089:067:268)(0105130613:280:067:0"
                  "47:263)(0105131212:176:047:034:278)(0105131705:217:034:018:285)]][SK46PB12008:04:1071:0204132133:454:0["
                  "(0105130000:253:064:045:263)(0105130506:215:045:028:283)(0105130945:078:028:022:277)(0105131250:112:022"
                  ":013:280)]][SK47PB12008:04:0682:0204131232:216:0[(0105130000:141:057:045:274)(0105130313:318:045:019:28"
                  "7)(0105130949:175:019:003:272)(0105131415:499:003:000:267)]][SK48PB12008:04:0776:0104132355:329:1[(0105"
                  "130000:406:099:070:288)(0105130745:158:070:056:261)(0105131136:458:056:017:283)(0105132018:309:017:000:"
                  "286)]][SK49LI19005:04:0718:0104131537:221:0[(0105130000:115:071:060:269)(0105130340:242:060:035:262)(01"
                  "05130855:232:035:016:274)(0105131342:410:016:000:288)]][SK50LI19005:04:1298:0204131047:611:0[(010513000"
                  "0:389:098:068:275)(0105130822:163:068:056:277)(0105131229:223:056:036:276)(0105131738:261:036:014:276)]"
                  "][SK51LI19005:04:0147:0104131312:615:1[(0105130000:469:062:023:266)(0105130943:060:023:018:280)(0105131"
                  "202:032:018:015:286)(0105131403:052:015:011:259)]][SK52PB12008:04:1076:0204131134:382:0[(0105130000:255"
                  ":075:054:260)(0105130512:107:054:046:285)(0105130816:108:046:038:277)(0105131145:198:038:024:281)]][SK5"
                  "3PB12008:04:0518:0204132040:640:1[(0105130000:474:082:042:278)(0105130926:153:042:030:276)(0105131323:1"
                  "43:030:019:266)(0105131700:296:019:000:288)]][SK54PB12008:04:0890:0204131050:161:1[(0105130000:199:075:0"
                  "61:283)(0105130445:171:061:049:264)(0105130905:251:049:028:266)(0105131412:060:028:023:279)]][SK55LI1900"
                  "5:04:1468:0204131920:493:1[(0105130000:227:086:070:269)(0105130541:237:070:046:270)(0105131100:500:046:0"
                  "04:260)(0105132052:100:004:000:267)]][SK56PB12008:04:0048:0104131110:490:1[(0105130000:379:059:030:267)("
                  "0105130805:024:030:028:260)(0105130954:133:028:018:272)(0105131326:374:018:000:264)]][SK57LI19005:04:069"
                  "9:0104132136:347:0[(0105130000:425:061:022:260)(0105130836:312:022:000:273)(0205130132:452:100:055:270)("
                  "0205131056:424:055:025:265)]][SK58LI19005:04:0790:0104131949:682:1[(0105130000:030:082:079:275)(01051301"
                  "27:271:079:052:274)(0105130700:111:052:042:286)(0105130951:191:042:027:262)]][SK59LI19005:04:1414:010413"
                  "1838:146:1[(0105130000:162:055:043:283)(0105130415:128:043:033:287)(0105130726:362:033:000:287)(01051314"
                  "49:281:000:000:260)]][SK60PB12008:04:0621:0104132221:520:1[(0105130000:241:096:079:266)(0105130600:471:0"
                  "79:036:281)(0105131516:402:036:000:277)(0205131039:432:100:067:272)]][SK61LI19005:04:1640:0104131119:395"
                  ":0[(0105130000:121:080:071:274)(0105130351:150:071:057:273)(0105130752:283:057:029:263)(0105131329:089:0"
                  "29:021:287)]][SK62PB12008:04:0780:0104131523:527:0[(0105130000:098:096:087:263)(0105130316:071:087:081:2"
                  "70)(0105130533:381:081:052:284)(0105131301:223:052:033:275)]][SK63LI19005:04:1827:0104131449:137:1[(0105"
                  "130000:141:096:083:269)(0105130330:316:083:061:259)(0105131042:477:061:021:269)(0105131953:370:021:000:2"
                  "59)]][SK64PB12008:04:0005:0104132242:405:1[(0105130000:357:076:046:275)(0105130741:423:046:004:280)(0105"
                  "131552:340:004:000:287)(0205130807:360:100:072:275)]][SK65LI19005:04:0038:0204131735:357:0[(0105130000:0"
                  "89:098:090:287)(0105130320:376:090:059:288)(0105131037:085:059:051:265)(0105131343:060:051:046:288)]][SK"
                  "66LI19005:04:1777:0204131411:332:0[(0105130000:289:083:061:264)(0105130544:135:061:051:282)(0105130937:2"
                  "74:051:028:285)(0105131512:199:028:014:273)]][SK67LI19005:04:1600:0204132150:689:0[(0105130000:400:075:0"
                  "44:288)(0105130734:112:044:036:272)(0105131052:062:036:031:280)(0105131246:458:031:000:268)]][SK68PB1200"
                  "8:04:1045:0104131658:690:1[(0105130000:104:062:055:269)(0105130312:115:055:045:261)(0105130611:363:045:0"
                  "17:277)(0105131339:095:017:008:266)]][SK69PB12008:04:0179:0104132011:113:0[(0105130000:203:062:045:271)("
                  "0105130429:121:045:035:275)(0105130829:379:035:006:270)(0105131557:386:006:000:281)]][SK70PB12008:04:019"
                  "3:0204132320:419:0[(0105130000:440:070:033:273)(0105130846:376:033:000:265)(0205130110:277:100:075:283)("
                  "0205130725:305:075:051:262)]][SK71PB12008:04:0298:0104132111:354:0[(0105130000:019:084:083:279)(01051302"
                  "05:131:083:072:288)(0105130541:245:072:050:266)(0105131049:035:050:048:261)]][SK72LI19005:04:1038:010413"
                  "1835:239:1[(0105130000:155:085:074:262)(0105130421:457:074:032:259)(0105131301:273:032:010:284)(01051318"
                  "56:369:010:000:281)]][SK73PB12008:04:0427:0204131825:226:1[(0105130000:439:074:037:278)(0105130906:059:0"
                  "37:033:272)(0105131108:084:033:026:272)(0105131401:390:026:000:265)]][SK74PB12008:04:0006:0204131123:427"
                  ":1[(0105130000:410:092:060:264)(0105130837:352:060:033:279)(0105131615:474:033:000:277)(0205131220:347:1"
                  "00:073:283)]][SK75PB12008:04:0565:0204131935:662:0[(0105130000:492:061:016:282)(0105130939:246:016:000:2"
                  "84)(0205130217:325:100:075:276)(0205130840:042:075:072:275)]][SK76PB12008:04:1002:0204131920:062:1[(0105"
                  "130000:328:091:061:280)(0105130717:121:061:049:265)(0105131054:192:049:035:280)(0105131539:335:035:010:2"
                  "78)]][SK77PB12008:04:1153:0104131653:324:1[(0105130000:311:061:033:267)(0105130655:194:033:013:277)(0105"
                  "131205:182:013:000:278)(0205130116:283:100:074:266)]][SK78LI19005:04:0300:0104131135:615:1[(0105130000:3"
                  "56:070:038:287)(0105130655:301:038:014:277)(0105131308:477:014:000:264)(0205131003:266:100:081:283)]][SK"
                  "79PB12008:04:0030:0104132310:673:0[(0105130000:317:071:042:265)(0105130623:154:042:030:262)(0105131004:3"
                  "93:030:000:262)(0205130443:384:100:062:271)]][SK80LI19005:04:0580:0204131222:420:0[(0105130000:090:072:0"
                  "63:286)(0105130227:152:063:051:259)(0105130550:143:051:037:261)(0105131008:245:037:018:277)]]");
void setup() {  
  lcd.begin(16,2);
  digitalWrite(13, LOW);
  lcd.print("    POWER ON");
  lcd.setCursor(0,1);
  lcd.print("   smartSOLAR   ");
  delay(4000);
  
  setUpModem();

  configureModem(IPaddress,port);
  
} 


void loop() { 
  String stringToSend = "";
  int startIndex = 0;
  boolean allSent = false;
  int bytesToSend = fullString.length();
  
  int packetsToSend = (bytesToSend / 300) + 1;
  
  connectToServer();
  lcd.clear();
  lcd.print("Data: " + String(packetsToSend) + " packets.");
  delay(1000);
  
  int currentPacket = 1;
  while(!allSent){//Can only sent 1000 characters at a time
     lcd.clear();
      lcd.print("Packet " + String(currentPacket) + " of " + String(packetsToSend) + ".");
  
     if(startIndex < (bytesToSend - 300)){ //If start index is less than 990 bytes from the end of string
       char extract[301];
         fullString.copy(extract,300,startIndex);
         stringToSend = extract + '\0';
         sendData(stringToSend);
         startIndex +=300;
     }else{
         int stillToSend = bytesToSend - startIndex+1;
         stillToSend = stillToSend;
         Serial.println(stillToSend);
         char extract[stillToSend+1];
        fullString.copy(extract, stillToSend, startIndex);
        stringToSend = extract + '\0';
        Serial.println(stringToSend);
        stringToSend = stringToSend + ";";
        sendData(stringToSend);
        allSent = true;
     } 
     currentPacket++;
  }
  
  String receivedData = receiveData();
  

  closeSocket();


  Serial.println("Received data:\n "+ receivedData);
  lcd.clear();
  lcd.print("Received SOH &  "); 
  lcd.setCursor(0,1);
  lcd.print("disabled status");
  delay(10000);
  
  lcd.clear();
  lcd.print("Waiting 60 secs.");
  Serial.println("Waiting 60 seconds...\n");
  delay(60000);
}

//Waits for +SIND: 4 to be returned, meaning modem is ready
void setUpModem(){
  lcd.clear();
  lcd.print("Modem set up...");

  lcd.setCursor(0,1);
  //Initalise serial ports for communication
  Serial.begin(9600); //Computer comms
  Serial1.begin(115200);//modem
  Serial.print("Starting SM5100B Communication...");
  lcd.print("Starting SM5100B");
  pinMode(13,OUTPUT);
  delay(3000);

  boolean registered = false;
  while(!registered){             //Loop until correct message returned
    receivedString = receiveFromModem(); //Receive message from modem
    if(receivedString.equals("+SIND: 11")){ //SIND 11 is the message that the SIM is registered with network
      lcd.setCursor(0,1);
      lcd.print("Registered on TM");
      Serial.println("\nModem is registered on network and ready to communicate.");
      registered = true;          //break out of loop
    }else{
      lcd.setCursor(0,1);
      lcd.print("No signal...    ");
      Serial.println("No network found.");
      delay(500);
    }
  }
  delay(2000);
  
  boolean gprs = false;
  while(!gprs){             //Loop until correct message returned
    Serial1.println("AT+CGATT?");
    receivedString = receiveFromModem(); //Receive message from modem
    Serial.print(receivedString);
    Serial.print('.');       //Show that something is happening each time message comes through
    if(receivedString.equals("+CGATT: 1")){ //message that the GPRS is available
      lcd.setCursor(0,1);
      lcd.print("GPRS available  ");
      Serial.println("\nGPRS found on network.");
      gprs = true;          //break out of loop
    }else{
      lcd.setCursor(0,1);
      lcd.print("No GPRS found   ");
      Serial.println("\nNo GPRS found on network.");
      delay(500);
    }
  }
  delay(2000);
  Serial.println("Ready for configuration...");
  lcd.clear();
  lcd.print("Configuring...");
  delay(1000);
}

//Configures modem with specified IP and port for remote server
//TODO include APN settings as parameters here.
void configureModem(String IPaddress, String port){
  int successfulCommands = 0; //This int is incremented each time a successful command goes through to stop
  //later commands being carried out after failed command

  do{
    //Set up PDP context
    Serial1.println("AT+CGDCONT=1,\"IP\",\"general.t-mobile.uk\"");
    delay(2000);
    receivedString = receiveFromModem(); //Receive message from modem
    if(receivedString.equals("OK")){ //OK is expected
      lcd.setCursor(0,1);
      lcd.print("PDP context set ");
      Serial.println("\n\tPDP context set up successfully.");
      successfulCommands++; //increment, therefore breaking out of loop.
    }
    else{
      Serial.println("Something went wrong, retrying");
    }
  }
  while(successfulCommands == 0);

  do{
    //Set up PDP context parameters (APN username/password)
    Serial1.println("AT+CGPCO=0,\"tmobile\",\"tm\",1");
    delay(2000);
    receivedString = receiveFromModem(); //Receive message from modem
    if(receivedString.equals("OK")){ //OK is expected
      Serial.println("\tPDP context parameters set up successfully.");
      lcd.setCursor(0,1);
      lcd.print("PDP params set  ");
      successfulCommands++; //increment, therefore breaking out of loop.
    }
  }
  while(successfulCommands <= 1);

  do{
    //Activate PDP context
    Serial1.println("AT+CGACT=1,1");
    delay(2000);
    receivedString = receiveFromModem(); //Receive message from modem
    //    Serial.println(receivedString);
    if(receivedString.equals("OK")){ //OK is expected
      Serial.println("\tPDP context activated.");
      lcd.setCursor(0,1);
      lcd.print("PDP cont. active");
      successfulCommands++; //increment, therefore breaking out of loop.
    }
  }
  while(successfulCommands <= 2);

  do{
    //Configure remote host and port, then a TCP connection can be opened
    String remoteConfiguration = "AT+SDATACONF=1, \"TCP\", \"";
    remoteConfiguration += IPaddress;
    remoteConfiguration += "\", ";
    remoteConfiguration += port;
    Serial1.println(remoteConfiguration);
    delay(2000);
    receivedString = receiveFromModem(); //Receive message from modem
    if(receivedString.equals("OK")){ //OK is expected
      Serial.println("\tTCP parameters for connection to remote server configured.");
      lcd.setCursor(0,1);
      lcd.print("TCP params set  ");
      successfulCommands++; //increment, therefore breaking out of loop.
    }
  }
  while(successfulCommands <= 3);
  
   do{
    //Configure remote host and port, then a TCP connection can be opened
    Serial1.println("AT+SDATARXMD=1,1");
    delay(2000);
    receivedString = receiveFromModem(); //Receive message from modem
    if(receivedString.equals("OK")){ //OK is expected
      Serial.println("\tReceive mode set to string rather than hex.");
      lcd.setCursor(0,1);
      lcd.print("RXMD String set ");
      successfulCommands++; //increment, therefore breaking out of loop.
    }
  }
  while(successfulCommands <= 4);

  delay(2000);

  Serial.println("\nSet up complete, ready to send over GPRS/GSM.");
  lcd.setCursor(0,1);
  lcd.print("complete.       ");
  delay(2000);
}

void connectToServer(){
  lcd.clear();
  lcd.print("Connecting serv.");

  int successfulConnect = 0;
  do{
    //Open connection
    Serial1.println("AT+SDATASTART=1,1");
    delay(2000);
    receivedString = receiveFromModem(); //Receive message from modem
    if(receivedString.equals("OK")){ //OK is expected
      Serial.println("\n\tAttempted to open socket.");
      lcd.setCursor(0,1);
      lcd.print("Opening socket  ");
      boolean querySuccess = false;
      do{
        //Check that socket is connected
        Serial1.println("AT+SDATASTATUS=1");
        delay(2000);
        receivedString = receiveFromModem(); //Receive message from modem
        String trimmedString = receivedString.substring(0,11);
        if(trimmedString.equals("+SOCKSTATUS")){ //This is the start of the returned message
          if(receivedString[16] == '1'){ //+SOCKSTATUS:  1,0,0000,0,0,0 this is the returned message
            querySuccess=true;            //16th character is 0 for not connected, 1 for connected
            successfulConnect++; //increment, therefore breaking out of main loop.
            Serial.println("\tConnected to remote server.");
            lcd.setCursor(0,1);
            lcd.print("Connected server");
            digitalWrite(13, HIGH);
            delay(2000);
          }
          else{
            Serial.println("\tUnsuccessful connection, trying again...");
            querySuccess= true;
            lcd.setCursor(0,1);
            lcd.print("Trying again... ");
            //no index increment

              //Send close socket command to ensure that modem has closed socket
            //before trying again.
            boolean successfulCommand=false;
            do{
              Serial1.println("AT+SDATASTART=1,0");
              delay(2000);
              receivedString = receiveFromModem(); //Receive message from modem
              if(receivedString.equals("OK")){ //OK is expected
                successfulCommand=true;
              }
            }
            while(!successfulCommand);
          }
        }
      }
      while(!querySuccess);
    }
  }
  while(successfulConnect == 0); 
  
}

//Called when data is required to be sent to remote server
void sendData(String sendString){
  int successfulSend = 0;
  
  //Send some data
  Serial.println("\tSending data...");
  lcd.setCursor(0,1);
  lcd.print("Sending...      ");
  delay(1000);
  String stringToSend = "AT+SSTRSEND=1, \"";
  stringToSend += sendString;
  stringToSend += "\"";
  Serial1.println(stringToSend);

  do{
    receivedString = receiveFromModem(); //Receive message from modem
    if(receivedString.equals("OK")){ //This is the start of the returned message
      Serial.println("\tData sent.");
      lcd.setCursor(0,1);
      lcd.print("Data sent.       ");
      delay(1000);
      successfulSend++; //increment, therefore breaking out of loop.      
    }
    else{
      Serial.println("\tStill waiting for data to send...");
      lcd.setCursor(0,1);
      lcd.print("Still sending...");
      delay(500);
    }
  }
  while(successfulSend == 0);
}

//Returns string received from the server
String receiveData(){
  lcd.clear();
  lcd.print("Waiting for RX  ");
  Serial.println("\n\tWaiting to receive data from remote server...");
  String message = "";
  
  int currentPacket = 1;
    do{ //Data is sent as packets of 50 bytes, final one terminated with a ';' so loop until this is found.
    boolean receivedData = false;
    while(!receivedData){
      String modemStatus = receiveFromModem();
      if(modemStatus.equals("+STCPD:1")){  //this message indicates data received from server
        Serial.println("\tData available from modem.");
        receivedData = true;
        lcd.setCursor(0,0);
        lcd.print("Receiving...    ");
      }
    }

     Serial1.println("AT+SDATAREAD=1");
     delay(1000);
     receivedString = receiveFromModem(); 
     lcd.setCursor(0,1);
     lcd.print("Packet " + String(currentPacket) + " read.");
     Serial.println("\tData read from modem.");
     message += receivedString.substring(8); //From index 9 to the end of the string
     currentPacket++;
   }while(message[message.length()-1] != ';');
  
  return message;
}

void closeSocket(){
      boolean successfulClose = false;
     //Close the socket
  do{
    Serial1.println("AT+SDATASTART=1,0");
    receivedString = receiveFromModem(); //Receive message from modem
    if(receivedString.equals("OK")){ //OK is expected
      Serial.println("\tSocket closed.\n");
      lcd.setCursor(0,1);
      lcd.print("Socket closed.  ");
      digitalWrite(13, LOW);
      successfulClose = true;
      delay(2000);
    }
  }
  while(!successfulClose);  
}

//Should be run when message is expected from modem
//Returns the message from modem that can be compared.
String receiveFromModem(){ 
  String inString="";
  char incoming = 0;
  boolean receivedMessage = false;

  while(!receivedMessage){  //while no message found
    if(Serial1.available()>0){ //Look for serial data
      incoming = Serial1.read(); //read one byte from buffer    
      if(incoming == '\n'){ //if the byte is the new line character (indicates end of modem message)
        inString.trim();   //Remove unnecessary white space (causes issues with.equals)
        if(inString.length()>0){
          return inString;  //return the string
        }
        else{
          inString = "";
        }
      }
      inString += incoming;  //else add to the message and look for another byte
    } 
  }
}
