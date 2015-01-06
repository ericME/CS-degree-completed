/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import java.util.Arrays;
import java.util.List;



import junit.framework.TestCase;





/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest_Eric()
   {
	   System.out.println("***testIsValid/Manual Eric***");
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println(" 1: " + urlVal.isValid("https://www.amazon.com"));
	   System.out.println(" 2: " + urlVal.isValid("http://www.amazon.com"));
	   System.out.println(" 3: " + urlVal.isValid("www.amazon.com"));
	   System.out.println(" 4: " + urlVal.isValid("amazon.com"));
	   System.out.println(" 5: " + urlVal.isValid("amazon"));
	   System.out.println(" 6: " + urlVal.isValid(" "));
	   System.out.println(" 7: " + urlVal.isValid("https://www.google.com"));
	   System.out.println(" 8: " + urlVal.isValid("http://www.google.com"));
	   System.out.println(" 9: " + urlVal.isValid("www.google.com"));
	   System.out.println("10: " + urlVal.isValid("google.com"));
	   System.out.println("11: " + urlVal.isValid("google"));
	   System.out.println("12: " + urlVal.isValid("https://www.example.com"));
	   System.out.println("13: " + urlVal.isValid("http://www.example.com"));
	   System.out.println("14: " + urlVal.isValid("http://example.com"));
	   System.out.println("15: " + urlVal.isValid("www.example.com"));
	   System.out.println("16: " + urlVal.isValid("example.com"));
	   System.out.println("17: " + urlVal.isValid("example"));
	   System.out.println("18: " + urlVal.isValid("http://www.iana.org/domains/reserved"));
	   System.out.println("19: " + urlVal.isValid("http://www.example.com/file1/file2"));
	   System.out.println("20: " + urlVal.isValid("ftp://www.example.com"));
	   System.out.println("21: " + urlVal.isValid("hps://www.wikipedia.org"));
	   System.out.println("22: " + urlVal.isValid("http://0.0.0.0:0/test1"));
	   System.out.println("23: " + urlVal.isValid("http://0.0.0.0/test1"));
	   System.out.println("24: " + urlVal.isValid("http://0.0.0.0:100/test1"));
	   System.out.println("25: " + urlVal.isValid("http://0.0.0.0:1000/test1"));
	   System.out.println("26: " + urlVal.isValid("http://www.amazon.com/nile?type=river&country=Egypt#name"));
	   urlVal = new UrlValidator(UrlValidator.ALLOW_LOCAL_URLS);
	   System.out.println("27: " + urlVal.isValid("http://localhost/test/index.html"));
	   urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println("28: " + urlVal.isValid("http://www.amazon.ye"));
   }
   public void testManualTest_Barbara()
   {
	   System.out.println("***testIsValid/Manual Barbara***");
       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       System.out.println(urlVal.isValid("http://www.amazon.,com"));
       System.out.println(urlVal.isValid("http:/www.amazon.com"));       
       System.out.println(urlVal.isValid("http://www.amazon.com/nile.txt"));
       System.out.println(urlVal.isValid("http://www.amazon.com/nile.txt/"));       
       System.out.println(urlVal.isValid("http://www.amazon.com/nile.txt/?type=river"));
       System.out.println(urlVal.isValid("http://www.amazon.com/nile.txt?type=river"));
       System.out.println(urlVal.isValid("http://www.amazon.com/nile.txt?type=river&country=Egypt"));
       System.out.println(urlVal.isValid("http://www.amazon.com/nile?type=river&country=Egypt#name"));
       
       System.out.println(urlVal.isValid("http://www.amazon.com/nile.txttype=river"));
       System.out.println(urlVal.isValid("http://www.amazon.com/nile.txttype=river&country=Egypt"));
       System.out.println(urlVal.isValid("http://www.amazon.com/niletype=river&country=Egypt#name"));
       System.out.println(urlVal.isValid("https://www.google.com/culturalinstitute/entity/%2Fm%2F06wfxz"));
       System.out.println(urlVal.isValid("http://www.amazon.com"));
       System.out.println(urlVal.isValid("http://www.amazon.com:1"));
       System.out.println(urlVal.isValid("http://www.amazon.com:65535"));
       System.out.println(urlVal.isValid("http://www.amazon.com:-1"));
       System.out.println(urlVal.isValid("http://www.amazon.com:6a"));
       System.out.println(urlVal.isValid("http://www.amazon.xxx"));
       System.out.println(urlVal.isValid("http://www.amazon.it"));
   }
   
   public void testManualTest_Lauren()
   {
	   System.out.println("***testIsValid/Manual Lauren***");
       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       System.out.println(urlVal.isValid("http://www.google.com"));
       System.out.println(urlVal.isValid("HTTP://www.google.com"));
       System.out.println(urlVal.isValid("HTTP://www.google.org"));
       System.out.println(urlVal.isValid("HTTP://www.google.co"));
       System.out.println(urlVal.isValid("HTTP://www.google.biz"));
       System.out.println(urlVal.isValid("HTTP://www.google.net"));
       System.out.println(urlVal.isValid("HTTP://www.google.info"));
       System.out.println(urlVal.isValid("HTTP://www.google.au"));
       System.out.println(urlVal.isValid("HTTP://www.google.false"));
       
   }
   
  
   //VALIDATOR-345
   //isValid() fails for port numbers longer than 3 digits
   public void testBug345() throws Throwable
   {
       int maxPorts = 65535;
       boolean errOccured = false;
       Throwable error = null;

       String url = "http://0.0.0.0:";
       
       System.out.println("***testIsValid/PORT test [BUG345]***");

       UrlValidator urlVal = new UrlValidator(null, null,    UrlValidator.ALLOW_ALL_SCHEMES);

       //test normal range

       for (int i = 1; i <= maxPorts; i*=10){

    	   System.out.println(url + i +":" + urlVal.isValid(url+i));
           if (i <= maxPorts)
        	   try{
        		   assertTrue("ports in bounds should validate",urlVal.isValid(url+i));
        	   }catch(AssertionError e){
        		   errOccured = true;
   		    	   error = e;
        	   }
       }

       //test low bounds

       System.out.println(url + "0" +":" + urlVal.isValid(url+"0"));
	   try{
		   assertTrue("lowest ports possible should validate", urlVal.isValid(url+"0"));
	   }catch(AssertionError e){
		   errOccured = true;
	    	   error = e;
	   }
       
       System.out.println(url +":" + urlVal.isValid(url));
       
	   try{
		   assertFalse("no port specified, should not validate", urlVal.isValid(url+":"));
	   }catch(AssertionError e){
		   errOccured = true;
	    	   error = e;
	   }
       System.out.println(url + "-1" +":" + urlVal.isValid(url+"-1"));
       
	   try{
		   assertFalse("improper port specified, should not validate", urlVal.isValid(url+"-1"));
	   }catch(AssertionError e){
		   errOccured = true;
	    	   error = e;
	   }
       //test upper bounds

       System.out.println(url + "99999" +":" + urlVal.isValid(url+"99999"));
       
	   try{
		   assertTrue("highest port specified, should validate", urlVal.isValid(url+"99999"));
	   }catch(AssertionError e){
		   errOccured = true;
	    	   error = e;
	   }
       System.out.println(url + "100000" +":" + urlVal.isValid(url+"100000"));
       
	   try{
		   assertFalse("improper port specified, should not validate", urlVal.isValid(url+"100000"));
	   }catch(AssertionError e){
		   errOccured = true;
	    	   error = e;
	   }

	   //test weird stuff
       System.out.println(url + "1.1" +":" + urlVal.isValid(url+"1.1"));
       
	   try{
		   assertFalse(urlVal.isValid(url+"1.1"));
	   }catch(AssertionError e){
		   errOccured = true;
	    	   error = e;
	   }
	   
       System.out.println(url + "A" +":" + urlVal.isValid(url+"A"));
	   try{
		   assertFalse(urlVal.isValid(url+"A"));
	   }catch(AssertionError e){
		   errOccured = true;
	    	   error = e;
	   }
       
       if (errOccured == true){
		   throw error;
	   }
   }
   
   //VALIDATOR-346
   //isValid() fails for urls with a query string
   public void testBug346() throws Throwable
   {
       boolean errOccured = false;
       Throwable error = null;
       
       String url = "http://www.google.com/";
      
       System.out.println("***testIsValid/query test [BUG346]***");

       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       
       String queries[] = new String[] {
    		"", //test blank query
    		"?type=river", //test acceptable queries
    		"?title=Hantavirus&action=edit&section=4",
    		"nile?type=river&country=Egypt#name"
       		};
	   List<String> querylist = Arrays.asList(queries);
	   

	   for (String q : querylist){
		   try{
			   
			   assertTrue("queries should validate",
					   urlVal.isValid(url + q));
			   
		       System.out.println(url + q +" - passed");
		       
		     }catch(AssertionError e){
		    	 
		    	System.out.println(url + q + " - failed");
		    	errOccured = true;
		    	error = e;
		     }
	   }
	   
	   if (errOccured == true){
		   throw error;
	   }
       

       
  }
   
   //VALIDATOR-347
   //isValid() fails for local urls
      public void testBug347() throws Throwable
   {
	   //init our validator to look for local urls
	   UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_LOCAL_URLS);
	   //need to suppress any errors until the end
	   boolean errOccured = false;
	   Throwable error = null;
	   //check urls that should pass
	   String urlArray[] = new String[] { "http://localhost/test/index.html", "http://localhost/", "https://localhost/", "http://127.0.0.1" };
	   List<String> urlList = Arrays.asList(urlArray);
	   
	   System.out.println("***testIsValid/LOCAL DOMAIN test [BUG347]***");

	   for (String url : urlList){
		   try{
			   
			   assertTrue("local URLs should validate",
					   urlVal.isValid(url));
			   
		       System.out.println(url + " - passed");
		       
		     }catch(AssertionError e){
		    	 
		    	System.out.println(url + " - failed");
		    	errOccured = true;
		    	error = e;
		     }
	   }
	   
	   if (errOccured == true){
		   throw error;
	   }

   }
      //VALIDATOR-348
      //isValid() fails for urls with valid country code tld�s
      public void testBug348() throws Throwable{
   	   //init our validator to look for local tlds
   	   UrlValidator tldVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
   	   //need to suppress any errors until the end
   	   boolean errOccured = false;
   	   Throwable error = null;
   	   //check tlds that should pass
   	   String tldArray[] = new String[] {
   		        "ac",                 // Ascension Island
   		        "ad",                 // Andorra
   		        "ae",                 // United Arab Emirates
   		        "af",                 // Afghanistan
   		        "ag",                 // Antigua and Barbuda
   		        "ai",                 // Anguilla
   		        "al",                 // Albania
   		        "am",                 // Armenia
   		        "an",                 // Netherlands Antilles
   		        "ao",                 // Angola
   		        "aq",                 // Antarctica
   		        "ar",                 // Argentina
   		        "as",                 // American Samoa
   		        "at",                 // Austria
   		        "au",                 // Australia (includes Ashmore and Cartier Islands and Coral Sea Islands)
   		        "aw",                 // Aruba
   		        "ax",                 // Åland
   		        "az",                 // Azerbaijan
   		        "ba",                 // Bosnia and Herzegovina
   		        "bb",                 // Barbados
   		        "bd",                 // Bangladesh
   		        "be",                 // Belgium
   		        "bf",                 // Burkina Faso
   		        "bg",                 // Bulgaria
   		        "bh",                 // Bahrain
   		        "bi",                 // Burundi
   		        "bj",                 // Benin
   		        "bm",                 // Bermuda
   		        "bn",                 // Brunei Darussalam
   		        "bo",                 // Bolivia
   		        "br",                 // Brazil
   		        "bs",                 // Bahamas
   		        "bt",                 // Bhutan
   		        "bv",                 // Bouvet Island
   		        "bw",                 // Botswana
   		        "by",                 // Belarus
   		        "bz",                 // Belize
   		        "ca",                 // Canada
   		        "cc",                 // Cocos (Keeling) Islands
   		        "cd",                 // Democratic Republic of the Congo (formerly Zaire)
   		        "cf",                 // Central African Republic
   		        "cg",                 // Republic of the Congo
   		        "ch",                 // Switzerland
   		        "ci",                 // Côte d'Ivoire
   		        "ck",                 // Cook Islands
   		        "cl",                 // Chile
   		        "cm",                 // Cameroon
   		        "cn",                 // China, mainland
   		        "co",                 // Colombia
   		        "cr",                 // Costa Rica
   		        "cu",                 // Cuba
   		        "cv",                 // Cape Verde
   		        "cx",                 // Christmas Island
   		        "cy",                 // Cyprus
   		        "cz",                 // Czech Republic
   		        "de",                 // Germany
   		        "dj",                 // Djibouti
   		        "dk",                 // Denmark
   		        "dm",                 // Dominica
   		        "do",                 // Dominican Republic
   		        "dz",                 // Algeria
   		        "ec",                 // Ecuador
   		        "ee",                 // Estonia
   		        "eg",                 // Egypt
   		        "er",                 // Eritrea
   		        "es",                 // Spain
   		        "et",                 // Ethiopia
   		        "eu",                 // European Union
   		        "fi",                 // Finland
   		        "fj",                 // Fiji
   		        "fk",                 // Falkland Islands
   		        "fm",                 // Federated States of Micronesia
   		        "fo",                 // Faroe Islands
   		        "fr",                 // France
   		        "ga",                 // Gabon
   		        "gb",                 // Great Britain (United Kingdom)
   		        "gd",                 // Grenada
   		        "ge",                 // Georgia
   		        "gf",                 // French Guiana
   		        "gg",                 // Guernsey
   		        "gh",                 // Ghana
   		        "gi",                 // Gibraltar
   		        "gl",                 // Greenland
   		        "gm",                 // The Gambia
   		        "gn",                 // Guinea
   		        "gp",                 // Guadeloupe
   		        "gq",                 // Equatorial Guinea
   		        "gr",                 // Greece
   		        "gs",                 // South Georgia and the South Sandwich Islands
   		        "gt",                 // Guatemala
   		        "gu",                 // Guam
   		        "gw",                 // Guinea-Bissau
   		        "gy",                 // Guyana
   		        "hk",                 // Hong Kong
   		        "hm",                 // Heard Island and McDonald Islands
   		        "hn",                 // Honduras
   		        "hr",                 // Croatia (Hrvatska)
   		        "ht",                 // Haiti
   		        "hu",                 // Hungary
   		        "id",                 // Indonesia
   		        "ie",                 // Ireland (Éire)
   		        "il",                 // Israel
   		        "im",                 // Isle of Man
   		        "in",                 // India
   		        "io",                 // British Indian Ocean Territory
   		        "iq",                 // Iraq
   		        "ir",                 // Iran
   		        "is",                 // Iceland
   		        "it",                 // Italy
   		        "je",                 // Jersey
   		        "jm",                 // Jamaica
   		        "jo",                 // Jordan
   		        "jp",                 // Japan
   		        "ke",                 // Kenya
   		        "kg",                 // Kyrgyzstan
   		        "kh",                 // Cambodia (Khmer)
   		        "ki",                 // Kiribati
   		        "km",                 // Comoros
   		        "kn",                 // Saint Kitts and Nevis
   		        "kp",                 // North Korea
   		        "kr",                 // South Korea
   		        "kw",                 // Kuwait
   		        "ky",                 // Cayman Islands
   		        "kz",                 // Kazakhstan
   		        "la",                 // Laos (currently being marketed as the official domain for Los Angeles)
   		        "lb",                 // Lebanon
   		        "lc",                 // Saint Lucia
   		        "li",                 // Liechtenstein
   		        "lk",                 // Sri Lanka
   		        "lr",                 // Liberia
   		        "ls",                 // Lesotho
   		        "lt",                 // Lithuania
   		        "lu",                 // Luxembourg
   		        "lv",                 // Latvia
   		        "ly",                 // Libya
   		        "ma",                 // Morocco
   		        "mc",                 // Monaco
   		        "md",                 // Moldova
   		        "me",                 // Montenegro
   		        "mg",                 // Madagascar
   		        "mh",                 // Marshall Islands
   		        "mk",                 // Republic of Macedonia
   		        "ml",                 // Mali
   		        "mm",                 // Myanmar
   		        "mn",                 // Mongolia
   		        "mo",                 // Macau
   		        "mp",                 // Northern Mariana Islands
   		        "mq",                 // Martinique
   		        "mr",                 // Mauritania
   		        "ms",                 // Montserrat
   		        "mt",                 // Malta
   		        "mu",                 // Mauritius
   		        "mv",                 // Maldives
   		        "mw",                 // Malawi
   		        "mx",                 // Mexico
   		        "my",                 // Malaysia
   		        "mz",                 // Mozambique
   		        "na",                 // Namibia
   		        "nc",                 // New Caledonia
   		        "ne",                 // Niger
   		        "nf",                 // Norfolk Island
   		        "ng",                 // Nigeria
   		        "ni",                 // Nicaragua
   		        "nl",                 // Netherlands
   		        "no",                 // Norway
   		        "np",                 // Nepal
   		        "nr",                 // Nauru
   		        "nu",                 // Niue
   		        "nz",                 // New Zealand
   		        "om",                 // Oman
   		        "pa",                 // Panama
   		        "pe",                 // Peru
   		        "pf",                 // French Polynesia With Clipperton Island
   		        "pg",                 // Papua New Guinea
   		        "ph",                 // Philippines
   		        "pk",                 // Pakistan
   		        "pl",                 // Poland
   		        "pm",                 // Saint-Pierre and Miquelon
   		        "pn",                 // Pitcairn Islands
   		        "pr",                 // Puerto Rico
   		        "ps",                 // Palestinian territories (PA-controlled West Bank and Gaza Strip)
   		        "pt",                 // Portugal
   		        "pw",                 // Palau
   		        "py",                 // Paraguay
   		        "qa",                 // Qatar
   		        "re",                 // Réunion
   		        "ro",                 // Romania
   		        "rs",                 // Serbia
   		        "ru",                 // Russia
   		        "rw",                 // Rwanda
   		        "sa",                 // Saudi Arabia
   		        "sb",                 // Solomon Islands
   		        "sc",                 // Seychelles
   		        "sd",                 // Sudan
   		        "se",                 // Sweden
   		        "sg",                 // Singapore
   		        "sh",                 // Saint Helena
   		        "si",                 // Slovenia
   		        "sj",                 // Svalbard and Jan Mayen Islands Not in use (Norwegian dependencies; see .no)
   		        "sk",                 // Slovakia
   		        "sl",                 // Sierra Leone
   		        "sm",                 // San Marino
   		        "sn",                 // Senegal
   		        "so",                 // Somalia
   		        "sr",                 // Suriname
   		        "st",                 // São Tomé and Príncipe
   		        "su",                 // Soviet Union (deprecated)
   		        "sv",                 // El Salvador
   		        "sy",                 // Syria
   		        "sz",                 // Swaziland
   		        "tc",                 // Turks and Caicos Islands
   		        "td",                 // Chad
   		        "tf",                 // French Southern and Antarctic Lands
   		        "tg",                 // Togo
   		        "th",                 // Thailand
   		        "tj",                 // Tajikistan
   		        "tk",                 // Tokelau
   		        "tl",                 // East Timor (deprecated old code)
   		        "tm",                 // Turkmenistan
   		        "tn",                 // Tunisia
   		        "to",                 // Tonga
   		        "tp",                 // East Timor
   		        "tr",                 // Turkey
   		        "tt",                 // Trinidad and Tobago
   		        "tv",                 // Tuvalu
   		        "tw",                 // Taiwan, Republic of China
   		        "tz",                 // Tanzania
   		        "ua",                 // Ukraine
   		        "ug",                 // Uganda
   		        "uk",                 // United Kingdom
   		        "um",                 // United States Minor Outlying Islands
   		        "us",                 // United States of America
   		        "uy",                 // Uruguay
   		        "uz",                 // Uzbekistan
   		        "va",                 // Vatican City State
   		        "vc",                 // Saint Vincent and the Grenadines
   		        "ve",                 // Venezuela
   		        "vg",                 // British Virgin Islands
   		        "vi",                 // U.S. Virgin Islands
   		        "vn",                 // Vietnam
   		        "vu",                 // Vanuatu
   		        "wf",                 // Wallis and Futuna
   		        "ws",                 // Samoa (formerly Western Samoa)
   		        "ye",                 // Yemen
   		        "yt",                 // Mayotte
   		        "yu",                 // Serbia and Montenegro (originally Yugoslavia)
   		        "za",                 // South Africa
   		        "zm",                 // Zambia
   		        "zw",                 // Zimbabwe
   		    };
   	   List<String> tldList = Arrays.asList(tldArray);
   	   
   	   String url = "http://www.amazon.";
   	   
   	System.out.println("***testIsValid/COUNTRY CODE TLD test [BUG348]***");
   	   for (String tld : tldList){
   		   try{
   			   
   			   assertTrue(tld + " is a valid TLD",
   					   tldVal.isValid(url + tld));
   			   
   		       System.out.println(tld + " - passed");
   		       
   		     }catch(AssertionError e){
   		    	 
   		    	System.out.println(tld + " - failed");
   		    	errOccured = true;
   		    	error = e;
   		     }
   	   }
   	   
   	   if (errOccured == true){
   		   throw error;
   	   }
      } 
   
   

}
