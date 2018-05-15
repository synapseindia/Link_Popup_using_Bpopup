<?php

/**
 * @file
 * Template to display menu links as a popup module example.
 */

?>
<div class="content">
  <p>To include link popup or open a link a popup window use the attribute <strong>rel="link-popup"</strong> when creating link. More animations can be included with link like slide up, slide down.</p>
  <h3>Example links for Link Pop Up</h3>
  <h4>Click on the Links</h4>
  <div class="lpopup_examples">
    <div class="lpopup_example">
      <h4>Deafult attribute: href="/lpop_up_display"</h4> 
      <?php
        $query_string = array();
        print l(t('Default link'), '/lpop_up_display', array('attributes' => array('rel' => 'link-popup'), 'query' => $query_string));
      ?>
    </div>
    <div class="lpopup_example">
      <h4>Slide from top: href="/lpop_up_display?slide=top"</h4> 
      <?php
        $query_string = array('slide' => 'top');
        print l(t('Slide from Top'), '/lpop_up_display', array('attributes' => array('rel' => 'link-popup'), 'query' => $query_string ));
      ?>
    </div>
    <div class="lpopup_example">
      <h4>Slide from bottom and height/width: href="/lpop_up_display?width=700&height=650&slide=bottom"</h4> 
      <?php
        $query_string = array('slide' => 'bottom', 'width' => '700', 'height' => '650');
        print l(t('Slide from bottom and height/width'), '/lpop_up_display', array('attributes' => array('rel' => 'link-popup'), 'query' => $query_string));
      ?>
    </div>
    <div class="lpopup_example">
      <h4>Slide from left and height/width: href="/lpop_up_display?width=700&height=650&slide=left"</h4> 
      <?php
        $query_string = array('slide' => 'left', 'width' => '700', 'height' => '650');
        print l(t('Slide from left and height/width'), '/lpop_up_display', array('attributes' => array('rel' => 'link-popup'), 'query' => $query_string));
      ?>
    </div>
    <div class="lpopup_example">
      <h4>Slide from right and height/width: href="/lpop_up_display?width=700&height=650&slide=right"</h4> 
      <?php
        $query_string = array('slide' => 'right', 'width' => '700', 'height' => '650');
        print l(t('Slide from right and height/width'), '/lpop_up_display', array('attributes' => array('rel' => 'link-popup'), 'query' => $query_string));
      ?>
    </div>
  </div>
</div>

