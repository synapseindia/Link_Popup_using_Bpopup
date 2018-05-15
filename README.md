# Link_Popup_using_Bpopup
Link Popup - Open Link in Pop up - use bPopup

This module will allow to open the links in drupal in popup whether it is node link or any custom page link.
To do so one has to add attribute rel="link-popup" in the link tag.

This module requires the bPopup library which can be downloaded from:
http://dinbror.dk/bpopup/
OR
https://github.com/dinbror/bpopup

Download and place the library in sites/all/libraries folder and the path to the library file should be:
sites/all/libraries/lpop_up/jquery.bpopup.min.js

Example to create url:

Deafult Example =>
$query_string = array('slide'=>'top');
$url = l(t('Link text'), 'path-to-link', array('attributes' => array('class' => array('about-link','another-class'), 'rel' => 'link-popup'), 'query' => $query_string));

Example with Height/Width =>
$query_string = array('slide'=>'top', 'width'=>'700', 'height'=>'650');
$url = l(t('Link text'), 'path-to-link', array('attributes' => array('class' => array('about-link','another-class'), 'rel' => 'link-popup'), 'query' => $query_string));
