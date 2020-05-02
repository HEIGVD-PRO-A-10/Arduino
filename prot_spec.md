# Spécifications des communications entre le terminal et l'API

#### codes ESP Mega

###### commands
```
0x20 : Login
0x30 : Transaction
0x50 : new User 
```
###### Return codes

**Success 0xD0 -> 0xFF**
```
0xD0 : Login OK
0xD1 : Transaction OK
0xD2 : New user ok
0xFF : WiFi OK
```

**Error 0xA0 -> 0xCF**
```
0xA0 : Login Wrong param
0xA1 : Wrong Login
0xA2 : Transaction card not valid
0xA3 : Transaction not enough credit
0xA4 : New User error
...
0xCD : Token not valid
0xCE : Unkown error 
0xCF : No Wifi
```
## Login

#### OK

```sequence
participant MEGA as mega
participant ESP as esp
participant API as api
mega -> esp : code 0x20[1byte], tag_rfid[4bytes], pin[4bytes]
esp -> api: GET /login {tag_rfid, pin_terminal}
api -> esp: 200 : Response JWT token
esp -> mega: code ok (0xD0)[1byte]
```
#### Param NOK
```sequence
participant MEGA as mega
participant ESP as esp
participant API as api
mega -> esp : code 0x20[1byte], tag_rfid[4bytes], pin[4bytes]
esp -> api: GET /login {tag_rfid, pin_terminal}
api -> esp: 400 : Response wrong Params
esp -> mega: code ko (0xA0)[1byte]
```

#### Non-autorisé
```sequence
participant MEGA as mega
participant ESP as esp
participant API as api
mega -> esp : code 0x20[1byte], tag_rfid[4bytes], pin[4bytes]
esp -> api: GET /login {tag_rfid, pin_terminal}
api -> esp: 401 : Response not autorised
esp -> mega: code ko (0xA1)[1byte]
```
## Transaction 
#### OK
```sequence
participant MEGA as mega
participant ESP as esp
participant API as api
mega -> esp : code 0x30[1byte], tag_rfid[4bytes], amount[1byte]
esp -> api: POST /transaction {tag_rfid, amount, num_terminal, jwt_token}
api -> esp: 201 : ok
esp -> mega: code ok (0xD1)[1byte]
```
#### Token not valid
```sequence
participant MEGA as mega
participant ESP as esp
participant API as api
mega -> esp : code 0x30[1byte], tag_rfid[4bytes], amount[1byte]
esp -> api: POST /transaction {tag_rfid, amount, num_terminal, jwt_token}
api -> esp: 401 : Not authorized
esp -> mega: code ko (0xCD)[1byte]
```
#### Card not valid

```sequence
participant MEGA as mega
participant ESP as esp
participant API as api
mega -> esp : code 0x30[1byte], tag_rfid[4bytes], amount[1byte]
esp -> api: POST /transaction {tag_rfid, amount, num_terminal, jwt_token}
api -> esp: TODO 401 : TODO
esp -> mega: code ko (0xA2)[1byte]
```

#### No credit
```sequence
participant MEGA as mega
participant ESP as esp
participant API as api
mega -> esp : code 0x30[1byte], tag_rfid[4bytes], amount[1byte]
esp -> api: POST /transaction {tag_rfid, amount, num_terminal, jwt_token}
api -> esp: TODO 401 : TODO
esp -> mega: code ko (0xA3)[1byte]
```


## Nouvel utilisateur 
#### OK
```sequence
participant MEGA as mega
participant ESP as esp
participant API as api
mega -> esp : code 0x50[1byte], tag_rfid[4bytes]
esp -> api: POST /transaction {tag_rfid, jwt_token}
api -> esp: 201 : ok
esp -> mega: code ok (0xD2)[1byte]
```
#### token not valid
```sequence
participant MEGA as mega
participant ESP as esp
participant API as api
mega -> esp : code 0x50[1byte], tag_rfid[4bytes]
esp -> api: POST /transaction {tag_rfid, jwt_token}
api -> esp: 401 : unauthorized
esp -> mega: code ko (0xCD)[1byte]
```

#### erreur
```sequence
participant MEGA as mega
participant ESP as esp
participant API as api
mega -> esp : code 0x50[1byte], tag_rfid[4bytes]
esp -> api: POST /transaction {tag_rfid, jwt_token}
api -> esp: 400 : error
esp -> mega: code ko (0xA4)[1byte]
```