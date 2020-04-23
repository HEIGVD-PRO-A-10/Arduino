# Spécifications des communications entre le terminal et l'API

## Login OK

```sequence
participant MEGA as mega
participant ESP as esp
participant API as api
mega -> esp : code 0x20[1byte], tag_rfid[4bytes], pin[4bytes]
esp -> api: GET /login {tag_rfid, pin_terminal}
api -> esp: Response JWT token
esp -> mega: code ok (0xE0)[1byte]
```

## Login Param NOK
```sequence
participant MEGA as mega
participant ESP as esp
participant API as api
mega -> esp : code 0x20[1byte], tag_rfid[4bytes], pin[4bytes]
esp -> api: GET /login {tag_rfid, pin_terminal}
api -> esp: Response wrong Params
esp -> mega: code ko (0xA0)[1byte]
```

## Login Non-autorisé
```sequence
participant MEGA as mega
participant ESP as esp
participant API as api
mega -> esp : code 0x20[1byte], tag_rfid[4bytes], pin[4bytes]
esp -> api: GET /login {tag_rfid, pin_terminal}
api -> esp: Response not autorised
esp -> mega: code ko (0xA1)[1byte]
```
## Débit OK

```sequence
participant MEGA as mega
participant ESP as esp
participant API as api
mega -> esp: code 0x21[1byte] client_tag_rfid[10bytes] amount[1byte] 
# api -> term: Response JWT token
esp -> api: GET /debit {tag_rfid=xxx, amount=10, JWT=xxx}
api -> esp: HTTP 200 {Status: SUCCESS}
esp -> mega: code ok 0xE1[1byte]
```

## Débit 

```sequence
participant Terminal as term
participant API as api
api -> term: Response JWT token
term -> api: GET /debit {tag_rfid=xxx, amount=50, JWT=xxx}
api -> term: HTTP 200 {Status: FAILURE, Message: "Pas assez d'argent"}
```

## Crédit OK

```sequence
participant Terminal as term
participant API as api
api -> term: Response JWT token
term -> api: GET /credit {tag_rfid=xxx, amount=10, JWT=xxx}
api -> term: HTTP 200 {Status: SUCCESS}
```

## Crédit erreur

```sequence
participant Terminal as term
participant API as api
api -> term: Response JWT token
term -> api: GET /credit {tag_rfid=xxx, amount=50, JWT=xxx}
api -> term: HTTP 200 {Status: FAILURE, Message: "Compte désactivé"}
```

## Nouvel utilisateur OK

```sequence
participant Terminal as term
participant API as api
api -> term: Response JWT token
term -> api: GET /new-user {tag_rfid=xxx, JWT=xxx}
api -> term: HTTP 200 {Status: SUCCESS}
```

## Nouvel utilisateur erreur

```sequence
participant Terminal as term
participant API as api
api -> term: Response JWT token
term -> api: GET /new-user {tag_rfid=xxx, JWT=xxx}
api -> term: HTTP 200 {Status: FAILURE, Message: "Tag déjà utilisé"}
```