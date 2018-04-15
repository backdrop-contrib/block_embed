<?php
/**
 * Administration page for Block Embed.
 */

/**
 * Administration form for embedding blocks.
 */
function block_embed_settings() {
  $config = config('block_embed.settings');
  $form = array('#config' => 'block_embed.settings');

  $all_types = node_type_get_names();
  asort($all_types);
  $types = $config->get('node_types');
  if (empty($types)) {
    $types = array_keys($all_types);
  }

  $block_options = array(
    'Custom Blocks' => array(),
    'Views Blocks' => array(),
  );

  $custom_blocks = config_get_names_with_prefix('block.custom');
  foreach ($custom_blocks as $file) {
    $block_options['Custom Blocks'][$file] = config_get($file, 'info');
  }

  $views_blocks = views_block_info();
  foreach ($views_blocks as $delta => $view) {
    $block_options['Views Blocks']['views.' . $delta] = $view['info'];
  }

  backdrop_alter('block_embed_options', $block_options);

  $form['block'] = array(
    '#type' => 'select',
    '#title' => t('Block to embed'),
    '#options' => $block_options,
    '#default_value' => $config->get('block'),
  );

  $form['position'] = array(
    '#type' => 'number',
    '#title' => t('Embed the block after'),
    '#field_suffix' => t('Paragraphs'),
    '#default_value' => $config->get('position'),
    '#min' => 0,
  );

  $form['node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Content types where a block should be embedded'),
    '#options' => $all_types,
    '#default_value' => $types,
  );

  return system_settings_form($form);
}
