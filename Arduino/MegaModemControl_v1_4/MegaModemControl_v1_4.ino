#include <LiquidCrystal.h>
#include <Flash.h>

//IP address and port of the remote server
String IPaddress = "176.250.25.30";
String port = "6100";

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

String receivedString = "";

FLASH_STRING(fullString, 
                  "[SK020413:80[0001:257,0005:263,0001:281,0004:305,0001:324,0005:346,0001:349,0251:360,0514:373,1034:391,2089:392,"
                  "4194:396,5211:374,6223:350,5214:326,4209:324,2136:308,1080:304,0558:289,0285:285,0004:280,0005:252,0002:227,0002"
                  ":203][SK01LI19005:04:0345:0204131158:090:0[(0104130000:383:062:033:260)(0104130759:413:033:000:279)(0204130125:3"
                  "38:100:069:267)(0204130801:405:069:032:263)]][SK02PB12008:04:0200:0104131654:218:1[(0104130000:056:090:086:270)(0"
                  "104130209:163:086:073:269)(0104130554:286:073:053:288)(0104131158:322:053:030:276)]][SK03LI19005:04:0511:02041321"
                  "36:650:0[(0104130000:278:070:049:259)(0104130637:438:049:009:274)(0104131545:204:009:000:284)(0204130608:071:100:"
                  "094:279)]][SK04PB12008:04:0448:0104132052:308:1[(0104130000:456:063:030:267)(0104130904:038:030:027:277)(01041311"
                  "25:140:027:016:273)(0104131510:437:016:000:269)]][SK05PB12008:04:0048:0104132054:524:0[(0104130000:442:071:037:28"
                  "5)(0104130859:399:037:004:270)(0104131710:162:004:000:279)(0204130653:461:100:062:272)]][SK06LI19005:04:1414:0204"
                  "131930:327:1[(0104130000:384:099:067:279)(0104130719:070:067:060:277)(0104130919:209:060:039:261)(0104131400:355:"
                  "039:010:273)]][SK07PB12008:04:1131:0204132044:624:1[(0104130000:453:088:056:281)(0104130918:034:056:053:286)(0104"
                  "131113:394:053:014:281)(0104131926:134:014:002:275)]][SK08PB12008:04:0735:0204131544:141:1[(0104130000:171:066:053"
                  ":272)(0104130432:492:053:012:260)(0104131344:489:012:000:283)(0204130940:415:100:062:276)]][SK09PB12008:04:0487:02"
                  "04131453:377:0[(0104130000:145:075:060:278)(0104130356:129:060:049:263)(0104130729:468:049:013:287)(0104131709:42"
                  "9:013:000:282)]][SK10PB12008:04:1019:0104131820:340:1[(0104130000:405:085:054:269)(0104130819:321:054:029:280)(01"
                  "04131528:274:029:002:278)(0104132054:465:002:000:283)]][SK11LI19005:04:0692:0204132135:696:0[(0104130000:231:092:"
                  "073:280)(0104130513:107:073:064:289)(0104130852:255:064:046:264)(0104131410:084:046:038:277)]][SK12LI19005:04:0678"
                  ":0104131457:509:0[(0104130000:287:054:030:269)(0104130643:290:030:008:268)(0104131240:078:008:001:263)(0104131541"
                  ":247:001:000:283)]][SK13LI19005:04:0335:0104131156:299:0[(0104130000:023:083:081:270)(0104130218:423:081:046:274)("
                  "0104131110:092:046:038:282)(0104131343:386:038:008:285)]][SK14PB12008:04:0485:0204132017:159:0[(0104130000:030:099"
                  ":097:272)(0104130126:135:097:084:260)(0104130435:342:084:056:259)(0104131137:375:056:018:265)]][SK15PB12008:04:028"
                  "7:0204131543:174:0[(0104130000:015:071:070:288)(0104130144:406:070:039:262)(0104130921:340:039:012:266)(0104131632"
                  ":203:012:000:271)]][SK16LI19005:04:0231:0104131657:524:0[(0104130000:070:082:077:278)(0104130241:130:077:064:283)("
                  "0104130644:060:064:059:268)(0104130849:327:059:029:285)]][SK17LI19005:04:1614:0204131753:565:0[(0104130000:424:053"
                  ":020:278)(0104130757:181:020:004:268)(0104131204:167:004:000:263)(0204130223:205:100:081:285)]][SK18LI19005:04:127"
                  "4:0204132144:467:1[(0104130000:149:074:060:264)(0104130327:466:060:022:259)(0104131248:134:022:012:270)(0104131556"
                  ":340:012:000:277)]][SK19LI19005:04:1804:0204131625:389:1[(0104130000:491:084:039:269)(0104130955:049:039:035:282)("
                  "0104131146:087:035:027:285)(0104131500:293:027:005:269)]][SK20PB12008:04:0634:0204131852:377:1[(0104130000:315:069:"
                  "046:267)(0104130623:243:046:024:280)(0104131133:159:024:012:289)(0104131503:024:012:010:283)]][SK21LI19005:04:0979"
                  ":0204131444:449:0[(0104130000:463:070:034:271)(0104130925:357:034:007:275)(0104131641:239:007:000:289)(0204130855:"
                  "476:100:063:263)]][SK22PB12008:04:0398:0104131147:567:1[(0104130000:355:094:064:274)(0104130703:366:064:036:282)(0"
                  "104131404:046:036:032:285)(0104131556:479:032:000:278)]][SK23LI19005:04:0399:0104132332:121:0[(0104130000:091:062:"
                  "054:267)(0104130325:397:054:015:274)(0104131059:152:015:001:260)(0104131520:164:001:000:287)]][SK24LI19005:04:1159"
                  ":0104132034:385:0[(0104130000:053:065:060:287)(0104130211:094:060:053:272)(0104130517:223:053:031:261)(0104131019:"
                  "155:031:019:274)]][SK25PB12008:04:0687:0104131518:651:0[(0104130000:157:052:036:260)(0104130342:210:036:017:274)(0"
                  "104130903:494:017:000:271)(0204130337:226:100:081:266)]][SK26LI19005:04:1718:0204131941:461:0[(0104130000:270:065:"
                  "042:266)(0104130620:440:042:006:264)(0104131532:149:006:000:272)(0204130608:285:100:078:287)]][SK27PB12008:04:0470"
                  ":0204131441:371:1[(0104130000:365:095:065:288)(0104130731:204:065:046:286)(0104131245:312:046:024:280)(0104131940:"
                  "055:024:019:270)]][SK28LI19005:04:1818:0104132147:487:0[(0104130000:119:092:080:289)(0104130353:378:080:042:278)(0"
                  "104131102:446:042:002:263)(0104131948:090:002:000:279)]][SK29LI19005:04:0559:0104131349:397:0[(0104130000:305:054:"
                  "032:266)(0104130652:166:032:019:267)(0104131122:011:019:018:281)(0104131317:168:018:006:287)]][SK30PB12008:04:0991"
                  ":0204131950:383:0[(0104130000:212:087:071:267)(0104130452:423:071:032:281)(0104131325:260:032:011:270)(0104131851:"
                  "148:011:000:266)]][SK31LI19005:04:0647:0204131614:693:0[(0104130000:183:081:067:278)(0104130442:364:067:041:269)(0"
                  "104131230:122:041:029:283)(0104131552:023:029:027:267)]][SK32LI19005:04:1568:0204131541:383:0[(0104130000:169:062:"
                  "048:281)(0104130356:027:048:046:269)(0104130518:466:046:003:283)(0104131457:455:003:000:279)]][SK33PB12008:04:0094"
                  ":0204131424:419:0[(0104130000:150:061:050:276)(0104130355:172:050:033:268)(0104130838:056:033:029:269)(0104131038:"
                  "245:029:012:282)]][SK34LI19005:04:0847:0204131723:137:1[(0104130000:188:079:060:259)(0104130440:227:060:043:272)(0"
                  "104131014:231:043:023:271)(0104131459:096:023:017:282)]][SK35PB12008:04:0437:0204131552:345:1[(0104130000:498:057:"
                  "007:283)(0104130954:356:007:000:281)(0204130402:029:100:097:285)(0204130613:046:097:093:283)]][SK36LI19005:04:1560"
                  ":0204131134:636:0[(0104130000:186:054:037:266)(0104130400:481:037:000:285)(0104131348:079:000:000:289)(0204130338:"
                  "490:100:062:263)]][SK37PB12008:04:0202:0104131529:188:0[(0104130000:454:068:023:270)(0104130847:282:023:000:281)(0"
                  "204130036:056:100:094:261)(0204130228:406:094:057:265)]][SK38PB12008:04:0226:0104131735:336:1[(0104130000:406:050:"
                  "019:288)(0104130819:119:019:008:264)(0104131207:380:008:000:264)(0204130450:288:100:079:267)]][SK39LI19005:04:0503"
                  ":0104132131:202:1[(0104130000:473:096:049:267)(0104130855:383:049:019:269)(0104131713:176:019:006:263)(0104132101:"
                  "137:006:000:265)]][SK40PB12008:04:0650:0104132214:310:1[(0104130000:278:070:050:261)(0104130530:489:050:013:283)(0"
                  "104131518:438:013:000:271)(0204130911:163:100:085:278)]][SK41PB12008:04:0167:0204131646:342:1[(0104130000:199:072:"
                  "054:272)(0104130517:143:054:042:280)(0104130859:152:042:027:272)(0104131226:187:027:012:262)]][SK42PB12008:04:0601"
                  ":0204131637:549:0[(0104130000:016:067:066:267)(0104130116:399:066:033:270)(0104130927:053:033:028:260)(0104131134:"
                  "326:028:003:266)]][SK43LI19005:04:1443:0104131221:511:1[(0104130000:433:069:036:271)(0104130855:219:036:019:264)(01"
                  "04131419:301:019:000:288)(0204130650:131:100:090:283)]][SK44PB12008:04:0459:0204131319:330:1[(0104130000:110:090:0"
                  "80:270)(0104130323:460:080:047:279)(0104131227:376:047:013:263)(0104132039:373:013:000:280)]][SK45PB12008:04:0394:"
                  "0204131848:299:0[(0104130000:029:063:061:286)(0104130207:122:061:049:284)(0104130500:153:049:037:264)(0104130900:1"
                  "03:037:030:286)]][SK46PB12008:04:1071:0104131058:246:1[(0104130000:499:075:033:288)(0104130956:277:033:012:285)(01"
                  "04131623:442:012:000:266)(0204131021:336:100:074:274)]][SK47PB12008:04:0682:0204131247:555:1[(0104130000:214:062:0"
                  "44:275)(0104130438:314:044:018:271)(0104131152:409:018:000:275)(0204130503:397:100:064:286)]][SK48PB12008:04:0776:"
                  "0204131124:429:0[(0104130000:485:100:056:272)(0104131003:377:056:024:288)(0104131745:284:024:000:267)(0204131059:3"
                  "58:100:070:289)]][SK49LI19005:04:0718:0104131810:672:1[(0104130000:411:057:025:288)(0104130847:208:025:008:270)(010"
                  "4131410:417:008:000:266)(0204130742:412:100:068:281)]][SK50LI19005:04:1298:0204131719:404:0[(0104130000:071:065:059"
                  ":276)(0104130302:312:059:036:276)(0104130939:243:036:014:281)(0104131442:037:014:011:279)]][SK51LI19005:04:0147:020"
                  "4131225:650:1[(0104130000:306:072:044:263)(0104130615:134:044:032:273)(0104131016:374:032:003:273)(0104131818:381:0"
                  "03:000:261)]][SK52PB12008:04:1076:0104131557:617:1[(0104130000:273:077:056:281)(0104130612:215:056:039:265)(0104131"
                  "037:426:039:007:260)(0104131909:472:007:000:272)]][SK53PB12008:04:0518:0204131949:272:1[(0104130000:023:075:073:282"
                  ")(0104130120:030:073:070:268)(0104130306:037:070:067:272)(0104130442:457:067:026:283)]][SK54PB12008:04:0890:0104131"
                  "335:165:1[(0104130000:166:100:087:286)(0104130424:267:087:068:282)(0104131038:110:068:060:279)(0104131335:073:060:0"
                  "53:269)]][SK55LI19005:04:1468:0204132255:636:1[(0104130000:290:096:074:277)(0104130624:459:074:032:289)(0104131549:"
                  "194:032:016:273)(0104132020:025:016:013:279)]][SK56PB12008:04:0048:0204132125:617:0[(0104130000:226:054:037:284)(01"
                  "04130440:496:037:000:274)(0204130057:259:100:076:272)(0204130614:060:076:071:272)]][SK57LI19005:04:0699:0104131357:"
                  "616:0[(0104130000:474:078:038:275)(0104130918:400:038:000:269)(0204130507:011:100:099:263)(0204130648:471:099:063:2"
                  "74)]][SK58LI19005:04:0790:0104131143:137:1[(0104130000:236:057:033:283)(0104130550:429:033:000:271)(0104131350:145:"
                  "000:000:271)(0204130441:335:100:076:260)]][SK59LI19005:04:1414:0104131816:074:0[(0104130000:097:055:048:263)(010413"
                  "0229:170:048:034:284)(0104130619:215:034:018:264)(0104131141:278:018:000:286)]][SK60PB12008:04:0621:0104131037:349:"
                  "1[(0104130000:302:091:068:276)(0104130651:291:068:047:268)(0104131245:276:047:024:269)(0104131826:122:024:014:259)]"
                  "][SK61LI19005:04:1640:0104131432:113:0[(0104130000:444:063:023:270)(0104130902:325:023:000:275)(0204130153:215:100:"
                  "082:262)(0204130713:228:082:063:289)]][SK62PB12008:04:0780:0104131328:116:0[(0104130000:410:054:022:274)(0104130847"
                  ":416:022:000:281)(0204130420:113:100:091:283)(0204130727:317:091:062:262)]][SK63LI19005:04:1827:0204131626:404:1[(0"
                  "104130000:047:062:058:262)(0104130234:311:058:032:287)(0104130903:081:032:025:281)(0104131209:252:025:006:266)]][SK"
                  "64PB12008:04:0005:0204131550:240:0[(0104130000:039:070:067:271)(0104130201:499:067:026:273)(0104131121:371:026:000:"
                  "273)(0204130542:026:100:098:280)]][SK65LI19005:04:0038:0104132053:125:0[(0104130000:376:086:052:278)(0104130738:145"
                  ":052:041:274)(0104131130:381:041:006:264)(0104131943:406:006:000:284)]][SK66LI19005:04:1777:0104132157:609:0[(01041"
                  "30000:406:082:045:278)(0104130741:458:045:012:275)(0104131654:044:012:009:264)(0104131917:211:009:000:259)]][SK67LI"
                  "19005:04:1600:0104131150:524:1[(0104130000:090:086:078:282)(0104130301:155:078:067:265)(0104130631:107:067:058:282)"
                  "(0104130908:128:058:048:278)]][SK68PB12008:04:1045:0204132015:521:1[(0104130000:204:056:039:271)(0104130426:325:039"
                  ":009:283)(0104131059:039:009:006:269)(0104131259:023:006:004:286)]][SK69PB12008:04:0179:0104132136:108:0[(010413000"
                  "0:328:062:032:289)(0104130657:154:032:020:285)(0104131053:381:020:000:280)(0204130422:242:100:078:262)]][SK70PB1200"
                  "8:04:0193:0204132042:208:0[(0104130000:317:070:044:273)(0104130633:277:044:022:275)(0104131243:138:022:010:289)(010"
                  "4131615:317:010:000:279)]][SK71PB12008:04:0298:0204131655:537:0[(0104130000:260:066:044:264)(0104130523:185:044:029"
                  ":277)(0104130944:058:029:024:265)(0104131209:461:024:000:280)]][SK72LI19005:04:1038:0104131015:296:1[(0104130000:458"
                  ":062:020:267)(0104130931:269:020:000:277)(0104132319:283:100:074:287)(0204130522:267:074:052:275)]][SK73PB12008:04:0"
                  "427:0104131257:398:0[(0104130000:365:094:066:269)(0104130719:387:066:034:268)(0104131439:330:034:001:283)(0104132110"
                  ":498:001:000:276)]][SK74PB12008:04:0006:0204131019:333:0[(0104130000:401:064:028:275)(0104130731:244:028:009:279)(01"
                  "04131305:177:009:000:274)(0204130228:245:100:081:278)]][SK75PB12008:04:0565:0204131942:484:1[(0104130000:315:092:063"
                  ":269)(0104130657:382:063:025:289)(0104131424:103:025:016:282)(0104131727:358:016:000:262)]][SK76PB12008:04:1002:0104"
                  "131221:581:1[(0104130000:292:065:036:273)(0104130558:040:036:032:280)(0104130825:363:032:006:285)(0104131606:176:006"
                  ":000:260)]][SK77PB12008:04:1153:0204131632:425:0[(0104130000:401:052:012:272)(0104130754:423:012:000:275)(0204130211"
                  ":239:100:080:273)(0204130736:382:080:051:265)]][SK78LI19005:04:0300:0104132144:299:1[(0104130000:408:089:055:289)(01"
                  "04130751:240:055:038:273)(0104131350:187:038:019:267)(0104131750:212:019:001:272)]][SK79PB12008:04:0030:0204131139:6"
                  "72:1[(0104130000:444:056:012:286)(0104130858:101:012:003:263)(0104131158:155:003:000:277)(0204130338:296:100:073:273"
                  ")]][SK80LI19005:04:0580:0104131750:142:1[(0104130000:098:072:064:273)(0104130259:196:064:049:265)(0104130754:104:049"
                  ":040:270)(0104131124:116:040:031:269)]]");
void setup() {  
  lcd.begin(16,2);
  digitalWrite(13, LOW);
  lcd.print("    POWER ON");
  delay(2300);
  
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


  boolean registered = false;
  while(!registered){             //Loop until correct message returned (not required if only one message required)
    receivedString = receiveFromModem(); //Receive message from modem
    Serial.print('.');       //Show that something is happening each time message comes through
    if(receivedString.equals("+SIND: 4")){ //SIND 4 is the message that the SIM is registered with network
      lcd.setCursor(0,1);
      lcd.print("Registered on TM");
      Serial.println("\nModem is registered on network and ready to communicate.");
      registered = true;          //break out of loop
    }
  }
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














