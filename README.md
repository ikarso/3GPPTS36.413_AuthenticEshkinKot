# 3GPPTS36.413_AuthenticEshkinKot
Import @AuthenticEshkinKot 3GPP TS 36.413 definitions and example application 

source https://github.com/vlm/asn1c/pull/115

# PR115

Just clone and build

Clone this repo

$ mkdir repo/code   
$ cd repo/code   
$ cp ../example/main_test.c .   
$ /path/to/asn1c -fcompound-names -gen-PER ../ASN/*.asn   

Edit Makefile.sample  
remove ASN_CONVERTER_SOURCES+=converter-sample.c  
add ASN_CONVERTER_SOURCES+=main_test.c  

$ make -f Makefile.am.sample  
$ ./progname ../data/test_data.org  

# PR125 with main_test.c

Clone PR125 and merge with PR99

Clone this repo

$ mkdir repo/code   
$ cd repo/code    
$ cp ../example/main_test_125.c .   
$ /path/to/asn1c -fcompound-names -gen-PER ../ASN/*.asn  

Edit Makefile.sample  
remove ASN_CONVERTER_SOURCES+=converter-sample.c  
add ASN_CONVERTER_SOURCES+=main_test_125.c  

$ make -f Makefile.am.sample  
$ ./progname ../data/test_data.org  
```
InitiatingMessage ::= {
    procedureCode: 11
    criticality: 1
    value: 
        00 00 03 00 00 00 05 C0 01 00 70 57 00 08 00 04 
        80 1B 46 FD 00 1A 00 32 31 27 84 78 93 EF 01 7C 
        54 88 B1 D4 52 15 C8 1D DA 18 22 04 45 49 63 8A 
        EB 67 85 24 E8 07 9D 60 01 32 A5 97 BE 07 7A 22 
        7B 98 DD D4 7D 97 E6 A0 1C 3D
}
procedureCode: 11
criticality: 1
size: 74
DownlinkNASTransport ::= {
    protocolIEs: ProtocolIE-Container ::= {
        ProtocolIE-Field ::= {
            id: 0
            criticality: 0
            value: C0 01 00 70 57
        }
        ProtocolIE-Field ::= {
            id: 8
            criticality: 0
            value: 80 1B 46 FD
        }
        ProtocolIE-Field ::= {
            id: 26
            criticality: 0
            value: 
                31 27 84 78 93 EF 01 7C 54 88 B1 D4 52 15 C8 1D 
                DA 18 22 04 45 49 63 8A EB 67 85 24 E8 07 9D 60 
                01 32 A5 97 BE 07 7A 22 7B 98 DD D4 7D 97 E6 A0 
                1C 3D
        }
    }
}

Field 0:
id 0
criticality 0
id_MME_UE = 16805975

Field 1:
id 8
criticality 0
id_eNB_UE = 1787645

Field 2:
id 26
criticality 0
```

# PR125

Clone PR125 and merge with PR99

Clone this repo

$ cd repo  
$ mkdir code  
$ cd code  
$ /path/to/asn1c -fcompound-names -gen-PER -pdu=InitiatingMessage ../ASN/*.asn  
$ make -f Makefile.am.sample  
$ ./progname -iaper ../data/InitiatingMessage  

```xml
<InitiatingMessage>
    <procedureCode>11</procedureCode>
    <criticality><ignore/></criticality>
    <value>
        00 00 03 00 00 00 05 C0 01 00 70 57 00 08 00 04 
        80 1B 46 FD 00 1A 00 32 31 27 84 78 93 EF 01 7C 
        54 88 B1 D4 52 15 C8 1D DA 18 22 04 45 49 63 8A 
        EB 67 85 24 E8 07 9D 60 01 32 A5 97 BE 07 7A 22 
        7B 98 DD D4 7D 97 E6 A0 1C 3D
    </value>
</InitiatingMessage>
```

$ /path/to/asn1c -fcompound-names -gen-PER -pdu=DownlinkNASTransport ../ASN/*.asn  
$ make -f Makefile.am.sample clean  
$ make -f Makefile.am.sample  
$ ./progname -iaper ../data/DownlinkNASTransport  

```xml
<DownlinkNASTransport>
    <protocolIEs>
        <ProtocolIE-Field>
            <id>0</id>
            <criticality><reject/></criticality>
            <value>C0 01 00 70 57</value>
        </ProtocolIE-Field>
        <ProtocolIE-Field>
            <id>8</id>
            <criticality><reject/></criticality>
            <value>80 1B 46 FD</value>
        </ProtocolIE-Field>
        <ProtocolIE-Field>
            <id>26</id>
            <criticality><reject/></criticality>
            <value>
                31 27 84 78 93 EF 01 7C 54 88 B1 D4 52 15 C8 1D 
                DA 18 22 04 45 49 63 8A EB 67 85 24 E8 07 9D 60 
                01 32 A5 97 BE 07 7A 22 7B 98 DD D4 7D 97 E6 A0 
                1C 3D
            </value>
        </ProtocolIE-Field>
    </protocolIEs>
</DownlinkNASTransport>
```
