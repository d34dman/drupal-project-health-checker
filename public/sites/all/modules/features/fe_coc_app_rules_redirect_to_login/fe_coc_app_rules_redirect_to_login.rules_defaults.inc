<?php
/**
 * @file
 * fe_coc_app_rules_redirect_to_login.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function fe_coc_app_rules_redirect_to_login_default_rules_configuration() {
  $items = array();
  $items['rules_coc_app_redirect_anonymous_user_to_login'] = entity_import('rules_config', '{ "rules_coc_app_redirect_anonymous_user_to_login" : {
      "LABEL" : "coc app redirect anonymous user to login",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "init" : [] },
      "IF" : [
        { "user_has_role" : {
            "account" : [ "site:current-user" ],
            "roles" : { "value" : { "1" : "1" } }
          }
        },
        { "NOT text_matches" : {
            "text" : [ "site:current-page:path" ],
            "match" : "user",
            "operation" : "starts"
          }
        }
      ],
      "DO" : [ { "redirect" : { "url" : "user\\/login", "destination" : "1" } } ]
    }
  }');
  return $items;
}
