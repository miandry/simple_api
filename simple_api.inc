<?php
/**
 * Created by PhpStorm.
 * User: ringier
 * Date: 19/10/17
 * Time: 5:31 PM
 */
namespace Drupal\simple_api;

class MigClass  {
   
    //renew
    function json_break_list($message){
         $ouput = array(
                    "data"=>array(),
                    "settings"=>array(
                        "message"=>$message,
                    )   
                ); 
         drupal_json_output($ouput);
         exit() ;
    }   
    function  get_vids(){
         $vocabulary = taxonomy_get_vocabularies();
         $results=[];
         foreach ($vocabulary as $key => $value) {
             $results[$key]=$value->machine_name ;
         }
         return $results ;
    }
    function entity_type_list(){
        return array("node","taxonomy_term","user");
    }
    function item_loader($entity){
        $items =[];

        foreach ($entity as $key => $value) {
              $field_type = ($this->field_mapper_field_type($key));
              $items[$key]= $value ;   
              //field_collection
              if($field_type=="field_collection"){
                 foreach ($value[LANGUAGE_NONE] as $key_collection => $collection) { 
                   $items[$key][LANGUAGE_NONE][$key_collection]['type']='field_collection';
                   $items[$key][LANGUAGE_NONE][$key_collection]["data_entity"] = field_collection_item_load($collection["value"]);
                 }              
              }
              //node reference
              if($field_type=="entityreference"){
                 foreach ($value[LANGUAGE_NONE] as $key_collection => $collection) { 
                   $items[$key][LANGUAGE_NONE][$key_collection]['type']='entityreference';  
                   $items[$key][LANGUAGE_NONE][$key_collection]["data_entity"] = node_load($collection["target_id"]);
                   $items[$key][LANGUAGE_NONE][$key_collection]["data_entity_user"] = user_load($collection["target_id"]);
                 } 
              }
              //taxonomy_term_reference 
              if($field_type=="taxonomy_term_reference"){
                 foreach ($value[LANGUAGE_NONE] as $key_collection => $collection) { 
                   $items[$key][LANGUAGE_NONE][$key_collection]['type']='taxonomy_term_reference';    
                   $items[$key][LANGUAGE_NONE][$key_collection]["data_entity"] = taxonomy_term_load($collection["tid"]);
                 } 
              }
               //image 
              if($field_type=="image"||$field_type=="file"){
                 foreach ($value[LANGUAGE_NONE] as $key_collection => $collection) { 
                   $items[$key][LANGUAGE_NONE][$key_collection][$field_type."_url"] = file_create_url($collection["uri"]);
                 } 
              }

        }
        return $items ;
    }
    function field_mapper_field_type($field_name) {
          $type_result = db_select('field_config', 'n')
              ->fields('n', array('type'))
              ->condition('field_name', $field_name, '=')
              ->range(0, 1)
              ->execute()
              ->fetchObject();
          if (is_object($type_result)) {
            return $type_result->type;
          }
          else {
            return null;
          }
    }
} 

