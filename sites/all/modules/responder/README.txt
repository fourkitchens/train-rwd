Responder helps you easily create responsive, mobile-first themes in
Drupal. It applies CSS3 @media queries to core and module CSS <link>
tags. This allows you to create mobile-aware layouts without having
to override countless module stylesheets.

Responder does NOT alter theme stylesheets or print stylesheets, only
CSS files added by Drupal core and contrib modules. It cache-aware and
will wrap media queries around the appropriate files. Configure the
media queries in the admin interface at /admin/config/media/responder


Example
---------------------
<link rel="stylesheet" media="all" href="/modules/node/node.css?1" />
                              ^^^
Turns into
                              vvvvvvvvvvvvvvvvvv
<link rel="stylesheet" media="(min-width: 960px)" href="/modules/node/node.css?1" />


Installation
---------------------
1) Install in /sites/all/modules
2) Enable module
3) Set media queries at /admin/config/media/responder

Original author: Chris Ruppel
