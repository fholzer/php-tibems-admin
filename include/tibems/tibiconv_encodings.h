/* 
 * Copyright 2001-2006 TIBCO Software Inc.
 * All rights reserved.
 * For more information, please contact:
 * TIBCO Software Inc., Palo Alto, California, USA
 * 
 * $Id: tibiconv_encodings.h 21731 2006-05-01 21:41:34Z $
 * 
 */

#ifndef _INCLUDED_tibiconv_encodings_h 
#define _INCLUDED_tibiconv_encodings_h 

/*************************************************************************
 * 
 * These are constant strings used as encoding arguments for calls to
 * tibiconv_ConvertFromUnicode() and tibiconv_ConvertToUnicode()
 * 
 ************************************************************************/

/* Standard JAVA encoding names can also be used */

#define TIBICONV_ASCII		"LATIN_1"
#define TIBICONV_UTF8		"UTF8"
#define TIBICONV_LATIN_1	"LATIN_1"
#define TIBICONV_UTF16	        "UTF16"
#define TIBICONV_UTF16BE	"UTF16_BigEndian"
#define TIBICONV_UTF16LE	"UTF16_LittleEndian"
#define TIBICONV_JIS		"ibm-943"

#define TIBICONV_TIBX_943	"tibx-943"
#define TIBICONV_TIBX_932	"tibx-932"
#define TIBICONV_EUC_JP		"eucJP"
#define TIBICONV_TIBX_EUC_JP	"tibx-eucJP"
#define TIBICONV_JAVA_EUC_JP	"java-EUC_JP-1.3_P"

#define TIBICONV_ISO_2022	"ISO_2022"
#define TIBICONV_EBCDIC_XML_US	"ebcdic-xml-us"
#define TIBICONV_IBM_912	"ibm-912"
#define TIBICONV_IBM_913	"ibm-913"
#define TIBICONV_IBM_914	"ibm-914"
#define TIBICONV_IBM_915	"ibm-915"
#define TIBICONV_IBM_1089	"ibm-1089"
#define TIBICONV_IBM_4909	"ibm-4909"
#define TIBICONV_IBM_813	"ibm-813"
#define TIBICONV_IBM_916	"ibm-916"
#define TIBICONV_IBM_920	"ibm-920"
#define TIBICONV_IBM_923	"ibm-923"
#define TIBICONV_IBM_1252	"ibm-1252"
#define TIBICONV_IBM_943	"ibm-943"
#define TIBICONV_IBM_949	"ibm-949"
#define TIBICONV_IBM_1370	"ibm-1370"
#define TIBICONV_IBM_950	"ibm-950"
#define TIBICONV_IBM_1386	"ibm-1386"
#define TIBICONV_IBM_970	"ibm-970"
#define TIBICONV_IBM_1361	"ibm-1361"
#define TIBICONV_IBM_1383	"ibm-1383"
#define TIBICONV_IBM_874	"ibm-874"
#define TIBICONV_IBM_437	"ibm-437"
#define TIBICONV_IBM_850	"ibm-850"
#define TIBICONV_IBM_858	"ibm-858"
#define TIBICONV_IBM_9044	"ibm-9044"
#define TIBICONV_IBM_852	"ibm-852"
#define TIBICONV_IBM_872	"ibm-872"
#define TIBICONV_IBM_855	"ibm-855"
#define TIBICONV_IBM_856	"ibm-856"
#define TIBICONV_IBM_9049	"ibm-9049"
#define TIBICONV_IBM_857	"ibm-857"
#define TIBICONV_IBM_859	"ibm-859"
#define TIBICONV_IBM_860	"ibm-860"
#define TIBICONV_IBM_861	"ibm-861"
#define TIBICONV_IBM_867	"ibm-867"
#define TIBICONV_IBM_862	"ibm-862"
#define TIBICONV_IBM_863	"ibm-863"
#define TIBICONV_IBM_17248	"ibm-17248"
#define TIBICONV_IBM_864	"ibm-864"
#define TIBICONV_IBM_865	"ibm-865"
#define TIBICONV_IBM_808	"ibm-808"
#define TIBICONV_IBM_866	"ibm-866"
#define TIBICONV_IBM_868	"ibm-868"
#define TIBICONV_IBM_9061	"ibm-9061"
#define TIBICONV_IBM_869	"ibm-869"
#define TIBICONV_IBM_878	"ibm-878"
#define TIBICONV_IBM_901	"ibm-901"
#define TIBICONV_IBM_921	"ibm-921"
#define TIBICONV_IBM_902	"ibm-902"
#define TIBICONV_IBM_922	"ibm-922"
#define TIBICONV_IBM_942	"ibm-942"
#define TIBICONV_IBM_1038	"ibm-1038"
#define TIBICONV_IBM_5346	"ibm-5346"
#define TIBICONV_IBM_5347	"ibm-5347"
#define TIBICONV_IBM_5349	"ibm-5349"
#define TIBICONV_IBM_5350	"ibm-5350"
#define TIBICONV_IBM_5351	"ibm-5351"
#define TIBICONV_IBM_5352	"ibm-5352"
#define TIBICONV_IBM_5353	"ibm-5353"
#define TIBICONV_IBM_5354	"ibm-5354"
#define TIBICONV_IBM_1250	"ibm-1250"
#define TIBICONV_IBM_1251	"ibm-1251"
#define TIBICONV_IBM_1253	"ibm-1253"
#define TIBICONV_IBM_1254	"ibm-1254"
#define TIBICONV_IBM_1255	"ibm-1255"
#define TIBICONV_IBM_1256	"ibm-1256"
#define TIBICONV_IBM_1257	"ibm-1257"
#define TIBICONV_IBM_1258	"ibm-1258"
#define TIBICONV_IBM_1275	"ibm-1275"
#define TIBICONV_IBM_1276	"ibm-1276"
#define TIBICONV_IBM_1277	"ibm-1277"
#define TIBICONV_IBM_1280	"ibm-1280"
#define TIBICONV_IBM_1281	"ibm-1281"
#define TIBICONV_IBM_1282	"ibm-1282"
#define TIBICONV_IBM_1283	"ibm-1283"
#define TIBICONV_IBM_849	"ibm-849"
#define TIBICONV_IBM_848	"ibm-848"
#define TIBICONV_IBM_5104	"ibm-5104"
#define TIBICONV_IBM_9238	"ibm-9238"
#define TIBICONV_IBM_1362	"ibm-1362"
#define TIBICONV_IBM_1363	"ibm-1363"
#define TIBICONV_IBM_5210	"ibm-5210"
#define TIBICONV_IBM_21427	"ibm-21427"
#define TIBICONV_IBM_37		"ibm-37"
#define TIBICONV_IBM_273	"ibm-273"
#define TIBICONV_IBM_277	"ibm-277"
#define TIBICONV_IBM_278	"ibm-278"
#define TIBICONV_IBM_280	"ibm-280"
#define TIBICONV_IBM_284	"ibm-284"
#define TIBICONV_IBM_285	"ibm-285"
#define TIBICONV_IBM_290	"ibm-290"
#define TIBICONV_IBM_297	"ibm-297"
#define TIBICONV_IBM_420	"ibm-420"
#define TIBICONV_IBM_424	"ibm-424"
#define TIBICONV_IBM_500	"ibm-500"
#define TIBICONV_IBM_803	"ibm-803"
#define TIBICONV_IBM_834	"ibm-834"
#define TIBICONV_IBM_835	"ibm-835"
#define TIBICONV_IBM_871	"ibm-871"
#define TIBICONV_IBM_930	"ibm-930"
#define TIBICONV_IBM_933	"ibm-933"
#define TIBICONV_IBM_935	"ibm-935"
#define TIBICONV_IBM_937	"ibm-937"
#define TIBICONV_IBM_939	"ibm-939"
#define TIBICONV_IBM_1390	"ibm-1390"
#define TIBICONV_IBM_1371	"ibm-1371"
#define TIBICONV_IBM_1047	"ibm-1047"
#define TIBICONV_IBM_1123	"ibm-1123"
#define TIBICONV_IBM_1140	"ibm-1140"
#define TIBICONV_IBM_1141	"ibm-1141"
#define TIBICONV_IBM_1142	"ibm-1142"
#define TIBICONV_IBM_1143	"ibm-1143"
#define TIBICONV_IBM_1144	"ibm-1144"
#define TIBICONV_IBM_1145	"ibm-1145"
#define TIBICONV_IBM_1146	"ibm-1146"
#define TIBICONV_IBM_1147	"ibm-1147"
#define TIBICONV_IBM_1148	"ibm-1148"
#define TIBICONV_IBM_1149	"ibm-1149"
#define TIBICONV_IBM_1153	"ibm-1153"
#define TIBICONV_IBM_1154	"ibm-1154"
#define TIBICONV_IBM_1155	"ibm-1155"
#define TIBICONV_IBM_1156	"ibm-1156"
#define TIBICONV_IBM_1157	"ibm-1157"
#define TIBICONV_IBM_1158	"ibm-1158"
#define TIBICONV_IBM_1159	"ibm-1159"
#define TIBICONV_IBM_1160	"ibm-1160"
#define TIBICONV_IBM_1164	"ibm-1164"
#define TIBICONV_IBM_1399	"ibm-1399"
#define TIBICONV_IBM_4930	"ibm-4930"
#define TIBICONV_IBM_1364	"ibm-1364"
#define TIBICONV_IBM_8482	"ibm-8482"
#define TIBICONV_IBM_4899	"ibm-4899"
#define TIBICONV_IBM_4971	"ibm-4971"
#define TIBICONV_IBM_9027	"ibm-9027"
#define TIBICONV_IBM_5123	"ibm-5123"
#define TIBICONV_IBM_12712	"ibm-12712"
#define TIBICONV_IBM_16684	"ibm-16684"
#define TIBICONV_IBM_16804	"ibm-16804"
#define TIBICONV_IBM_37_S390	"ibm-37-s390"
#define TIBICONV_IBM_1140_S390	"ibm-1140-s390"
#define TIBICONV_IBM_1142_S390	"ibm-1142-s390"
#define TIBICONV_IBM_1143_S390	"ibm-1143-s390"
#define TIBICONV_IBM_1144_S390	"ibm-1144-s390"
#define TIBICONV_IBM_1145_S390	"ibm-1145-s390"
#define TIBICONV_IBM_1146_S390	"ibm-1146-s390"
#define TIBICONV_IBM_1147_S390	"ibm-1147-s390"
#define TIBICONV_IBM_1148_S390	"ibm-1148-s390"
#define TIBICONV_IBM_1149_S390	"ibm-1149-s390"
#define TIBICONV_IBM_1153_S390	"ibm-1153-s390"
#define TIBICONV_IBM_12712_S390	"ibm-12712-s390"
#define TIBICONV_IBM_16804_S390	"ibm-16804-s390"


#endif

