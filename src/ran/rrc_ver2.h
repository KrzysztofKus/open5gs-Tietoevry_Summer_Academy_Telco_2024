#ifndef __RRC_VER2_H
#define __RRC_VER2_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#define NAS_ATTACH_REQUEST           0x01
#define NAS_AUTHENTICATION_REQUEST   0x02
#define NAS_SECURITY_MODE_COMMAND    0x03
#define NAS_REGISTRATION_REQUEST     0x04

typedef enum {
    RRC_SETUP_REQUEST,
    RRC_SETUP,
    RRC_SETUP_COMPLETE
} rrc_message_type_t;

typedef struct {
    uint8_t mode;  
    uint8_t sn_field_length;  
    bool is_reordering_enabled;  
    uint16_t max_retx_threshold;  
    uint8_t poll_pdu;  
    uint8_t poll_byte;  
    uint16_t poll_retransmit;  
} rlc_config_t;


typedef struct {
    uint8_t logicalChannelId;
    uint8_t priority;
    uint8_t lcGroup;
    uint8_t pdcpConfig;    
    rlc_config_t rlcConfig;     
} rb_config_t;

typedef struct {
    uint32_t mmeCode;      
    uint32_t mTmsi;        
} ue_identity_t;

typedef struct {
    rb_config_t radioBearerConfig; 
} rrc_setup_t;

typedef struct {
    ue_identity_t ueIdentity;            
    uint8_t establishmentCause;  // Establishment cause (e.g., emergency, highPriority)      
} rrc_setup_request_t;

typedef struct {
    ue_identity_t ueIdentity;  
    uint8_t capability;  
    uint8_t requestedNSSAI; 
    uint8_t lastVisitedTAI; 
    bool isEmergency;
} nas_registration_request_t;

typedef struct {
    uint8_t epsMobileIdentity;    
    uint8_t ueNetworkCapability;  
    uint8_t additionalUpdateType; 
    uint8_t lastVisitedRegisteredTAI; 
    uint8_t drxParameter; 
    bool isInitialAttach;
    uint8_t attachType;        
} nas_attach_request_t;

typedef struct {
    uint16_t rand;
    uint16_t autn;
} nas_authentication_request_t;

typedef struct {
    uint8_t selectedEncryptionAlgorithm;  
    uint8_t selectedIntegrityAlgorithm;   
    uint8_t nasSecurityAlgorithms;        
    uint8_t imeisvRequest;               
} nas_security_mode_command_t;

typedef struct {
    uint8_t messageType;
    uint8_t protocolDiscriminator;
    uint8_t securityHeaderType;
    uint8_t messageAuthenticationCode;
    bool integrityProtected;
    bool ciphered;
    union {
        nas_registration_request_t registrationRequest;
        nas_attach_request_t attachRequest;
        nas_authentication_request_t authRequest;
        nas_security_mode_command_t securityModeCommand;
    };
} nas_dedicated_message_t;

typedef struct {
    nas_dedicated_message_t NASMessage;  
} rrc_setup_complete_t;

void handle_rrc_setup_request(rrc_setup_request_t* setup_request);
void handle_rrc_setup_complete(rrc_setup_complete_t* setup_complete);

void rrc_dispatch_message(rrc_message_type_t msg_type, void* msg, uint16_t msg_size);

void send_message_to_mac(rrc_message_type_t msg_type, void* msg, uint16_t msg_size);
void* receive_message_from_ue(rrc_message_type_t* msg_type);

#ifdef __cplusplus
}
#endif

#endif /* __RRC_VER2_H */
