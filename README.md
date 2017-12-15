# simple_api
Drupal 7 Simple Api using For migration , it provide api to get List and Item of Node , User , Taxonomy
## Getting started
### 1. settings
Add Hash security in /sites/default/setting.php
```
$conf['simple_api_hash'] = 'XXXXXXXX';
```
Enable the module and that all ,you have API ready
```
drush en simple_api
```
### 2.Api Request Param
There are three main parameters


### 2.URL Request Example
```
/api/load_list?entity_type=YOUR_ENTITY_TYPE&entity_name=YOUR_ENTITY_NAME
```
