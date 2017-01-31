#include <stdio.h>
#include <sys/types.h>

#include <InitiatingMessage.h>
#include <UEContextReleaseCommand.h>
#include <HandoverRequired.h>
#include <InitialContextSetupResponse.h>
#include <UplinkNASTransport.h>
#include <Paging.h>
#include <InitialUEMessage.h>
#include <UECapabilityInfoIndication.h>
#include <DownlinkNASTransport.h>

#include <ProtocolIE-Field.h>
#include <ProtocolIE-Container.h>
#include <UE-S1AP-IDs.h>
#include <UEIdentityIndexValue.h>
#include <MME-UE-S1AP-ID.h>
#include <ENB-UE-S1AP-ID.h>
#include <Cause.h>
#include <CNDomain.h>
#include <ANY.h>
#include <TAI.h>
#include <EUTRAN-CGI.h>
#include <RRC-Establishment-Cause.h>

#define PARSE_CMD_(msg_type, DEF_Type, cont_type, field_type, msg_value)  \
  msg_type *msg = 0; \
  if (!ANY_to_type_aper(msg_value, &DEF_Type, (void **)&msg))  \
  { \
    asn_fprint(stdout, &DEF_Type, msg);  \
    cont_type * container = &(msg->protocolIEs);  \
    field_type ** field = (field_type**)container->list.array;  \
    int count = container->list.count, i; \
    for (i = 0; i != count; ++i)  \
    { \
      parseField(i, field[i]->id, field[i]->criticality, &(field[i]->value)); \
    } \
  } \
  else  \
  { \
    printf("-------Failed to cast msg_type\n"); \
  }

void processTAI(ANY_t * value)
{
  TAI_t *tai = 0;
  if (!ANY_to_type_aper(value, &asn_DEF_TAI, (void **)&tai))
  {
    //printf("tai.pLMNidentity = %d\n", tai->pLMNidentity);
    //printf("tai.tAC = %d\n", tai->tAC);
    asn_fprint(stdout, &asn_DEF_TAI, tai);
  }
}

void processCause(ANY_t * value)
{
  Cause_t *cause = 0;
  if (!ANY_to_type_aper(value, &asn_DEF_Cause, (void **)&cause))
  {
    printf("cause = %ld\n", cause->choice.radioNetwork);
    //asn_fprint(stdout, &asn_DEF_Cause, cause);
  }
}

void processCNDomain(ANY_t * value)
{
  CNDomain_t *cndomain = 0;
  if (!ANY_to_type_aper(value, &asn_DEF_CNDomain, (void **)&cndomain))
  {
    printf("cndomain = %ld\n", *cndomain);
    //asn_fprint(stdout, &asn_DEF_Cause, cause);
  }
}

void processUEIdentityIndexValue(ANY_t * value)
{
  UEIdentityIndexValue_t *ueidindex = 0;
  if (!ANY_to_type_aper(value, &asn_DEF_UEIdentityIndexValue, (void **)&ueidindex))
  {
    //printf("ueidindex = %d\n", ueidindex->buf);
    asn_fprint(stdout, &asn_DEF_UEIdentityIndexValue, ueidindex);
  }
}

void process_id_MME_UE(ANY_t * value)
{
  MME_UE_S1AP_ID_t *id_MME_UE = 0;
  if (!ANY_to_type_aper(value, &asn_DEF_MME_UE_S1AP_ID, (void **)&id_MME_UE))
  {
    printf("id_MME_UE = %ld\n", *id_MME_UE);
    //asn_fprint(stdout, &asn_DEF_Cause, cause);
  }
}

void process_id_eNB_UE(ANY_t * value)
{
  ENB_UE_S1AP_ID_t *id_eNB_UE = 0;
  if (!ANY_to_type_aper(value, &asn_DEF_ENB_UE_S1AP_ID, (void **)&id_eNB_UE))
  {
    printf("id_eNB_UE = %ld\n", *id_eNB_UE);
    //asn_fprint(stdout, &asn_DEF_Cause, cause);
  }
}

void processEutranCgi(ANY_t * value)
{
  EUTRAN_CGI_t *eutran_cgi = 0;
  if (!ANY_to_type_aper(value, &asn_DEF_EUTRAN_CGI, (void **)&eutran_cgi))
  {
    //printf("eutran_cgi = %d\n", *eutran_cgi);
    asn_fprint(stdout, &asn_DEF_EUTRAN_CGI, eutran_cgi);
  }
}

void processEstablishmentCause(ANY_t * value)
{
  RRC_Establishment_Cause_t *establishment_cause = 0;
  if (!ANY_to_type_aper(value, &asn_DEF_RRC_Establishment_Cause, (void **)&establishment_cause))
  {
    printf("establishment_cause = %ld\n", *establishment_cause);
    //asn_fprint(stdout, &asn_DEF_RRC_Establishment_Cause, establishment_cause);
  }
}

void parseField(int index, long id, long criticality, ANY_t * value)
{
  printf("\nField %d:\n", index);
  printf("id %ld\n", id);
  printf("criticality %ld\n", criticality);
    
  switch (id)
  {
    case 0: process_id_MME_UE(value); break;
    case 2: processCause(value); break;
    case 8: process_id_eNB_UE(value); break;
    case 67: processTAI(value); break;
    case 80: processUEIdentityIndexValue(value); break;
    case 100: processEutranCgi(value); break;
    case 109: processCNDomain(value); break;
    case 134: processEstablishmentCause(value); break;
    default: break;
  }
}

int main(int ac, char **av) {
    char buf[1024];      /* Temporary buffer      */
    InitiatingMessage_t *initMsg = 0; /* Type to decode */
    asn_dec_rval_t rval; /* Decoder return value  */
    FILE *fp;            /* Input file handler    */
    size_t size;         /* Number of bytes read  */
    char *filename;      /* Input file name */
 
    /* Require a single filename argument */
    if(ac != 2) {
      fprintf(stderr, "Usage: %s <file.ber>\n", av[0]);
      exit(64); /* better, EX_USAGE */
    } else {
      filename = av[1];
    }
 
    /* Open input file as read-only binary */
    fp = fopen(filename, "rb");
    if(!fp) {
      perror(filename);
      exit(66); /* better, EX_NOINPUT */
    }
  
    /* Read up to the buffer size */
    size = fread(buf, 1, sizeof(buf), fp);
    fclose(fp);
    if(!size) {
      fprintf(stderr, "%s: Empty or broken\n", filename);
      exit(65); /* better, EX_DATAERR */
    }
 
    /* Decode the input buffer as InitiatingMessage type */
    rval = aper_decode(0, &asn_DEF_InitiatingMessage,
      (void **)&initMsg, buf + 1, size - 1, 0, 0);
    if(rval.code != RC_OK) {
      fprintf(stderr,
        "%s: Broken InitiatingMessage encoding at byte %ld, size %ld, error code %d\n",
        filename, (long)rval.consumed, size, rval.code);
      exit(65); /* better, EX_DATAERR */
    }
    
    /* Print the decoded InitiatingMessage type as XML */
    asn_fprint(stdout, &asn_DEF_InitiatingMessage, initMsg);
    
    printf("procedureCode: %ld\n", initMsg->procedureCode);
    printf("criticality: %ld\n", initMsg->criticality);
    printf("size: %d\n", initMsg->value.size);
    
    PARSE_CMD_(DownlinkNASTransport_t, asn_DEF_DownlinkNASTransport, ProtocolIE_Container_123P31_t, ProtocolIE_Field_129P31_t, &(initMsg->value))
 
    return 0; /* Decoding finished successfully */
} 
