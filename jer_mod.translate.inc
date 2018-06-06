<?php

$googleAPIkey = '';

function jer_mod_tranlate_page() {
    return drupal_get_form('jer_mod_translate');
}

function jer_mod_translate(&$form_state) {
    $form = [];

    $form['#tree'] = TRUE;

    $form['from'] = [
        '#type' => 'fieldset',
        '#title' => t('Translate From'),
    ];

    $form['to'] = [
        '#type' => 'fieldset',
        '#title' => t('Translate To'),
    ];

    $form['from']['language'] = [
        '#type' => 'select',
        '#title' => t('Language'),
        '#options' => [
            'en' => t('English'),
            'fr' => t('French'),
            'es' => t('Spanish'),
        ],
        '#default_value' => 'english'

    ];

    $form['to']['language'] = [
        '#type' => 'select',
        '#title' => t('Language'),
        '#options' => [
            'en' => t('English'),
            'fr' => t('French'),
            'es' => t('Spanish'),
        ],
        '#default_value' => 'spanish'
    ];

    $form['from']['value'] = [
        '#type' => 'textarea',
        '#title' => t('Text'),
    ];

    $form['buttons']['submit'] = [
        '#type' => 'submit',
        '#value' => t('Submit'),
        '#executes_submit_callback' => TRUE
    ];

    return $form;
}

function jer_mod_translate_submit(&$form, &$form_state) {
    $url = 'https://translation.googleapis.com/language/translate/v2';
    $data = [
        'q' => $form_state['values']['from']['value'],
        'source' => $form_state['values']['from']['language'],
        'target' => $form_state['values']['to']['language'],
        'format' => 'text',

    ];

    $options = [
        'http' => [
            'header'  => [
                'Content-type' => 'application/json',
                'Authorization' => 'Bearer ' . $googleAPIkey
            ],
            'method'  => 'POST',
            'data' => http_build_query($data)
        ]
    ];

    $context  = stream_context_create($options);
    $result = file_get_contents($url, false, $context);
    if ($result === FALSE) {
        echo "An error has occured.";
    }
    
    $resArray = json_decode($result, true);
    $value = $resArray['data']['translations'];

    echo $value;
}