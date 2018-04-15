<?php
/**
 * API functions for block_embed module.
 */

/**
 * Implements hook_block_embed_options_alter().
 *
 * @param array $options
 *   Array of block embed options to be altered. Add additional options here.
 *   Note: please enure the block key provided is something that can be easily
 *   recognized in hook_block_embed_output().
 *
 * @see hook_block_embed_output().
 */
function hook_block_embed_options_alter(&$options) {
  // Add a single additional block.
  $options['User account blocks'] = array('user.login' => t('Log in block'));

  // Add a set of additonal blocks. @todo come up with a good example.
}

/**
 * Implements hook_block_embed_output().
 *
 * @param array $block_key
 *   This the key provided in hook_block_embed_options_alter().
 * @param string|NULL $output
 *   Markup to be embedded into content. Note: This should be NULL for your
 *   block before you begin.
 *
 * @see hook_block_embed_options_alter().
 */
function hook_block_embed_output($block_key, &$output) {
  if (empty($output) && substr($block_key, 0, 5) == 'user') {
    $output = backdrop_get_form('user_login_block');
  }

  return $output;
}
