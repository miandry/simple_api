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
There are three main parameters :
* [entity_type] -  can be take only three value : node,taxonomy_term,user
* [entity_name] - is the current entty name for example is entity)type=node and entity_name=article
* [page] - can be  node,taxonomy_term,user
* [limit] - can be  node,taxonomy_term,user
* [id] - can take value of nid,uid,tid depend on entity_type

### 2.URL Request Example
```
YOUR-DOMAIN-NAME/api/load_list?entity_type=YOUR_ENTITY_TYPE&entity_name=YOUR_ENTITY_NAME
```
