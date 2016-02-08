<?php print $messages; ?>
<div class="login-box">
  <div class="login-logo">
    <a href="/"><b>Clash</b> of <b>Clans</b></a>
  </div><!-- /.login-logo -->
  <div class="login-box-body clearfix">
    <p class="login-box-msg"><?php echo render($current_active_tab); ?></p>
    <section<?php print $content_column_class; ?>>
      <a id="main-content"></a>
      <?php if (!empty($tabs)): ?>
        <?php print render($tabs); ?>
      <?php endif; ?>
      <?php if (!empty($page['help'])): ?>
        <?php print render($page['help']); ?>
      <?php endif; ?>
      <?php if (!empty($action_links)): ?>
        <ul class="action-links"><?php print render($action_links); ?></ul>
      <?php endif; ?>
      <?php print render($page['content']); ?>
    </section>
  </div><!-- /.login-box-body -->
</div><!-- /.login-box -->

