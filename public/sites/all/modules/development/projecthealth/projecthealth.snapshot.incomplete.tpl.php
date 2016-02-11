<section class="content">
  <div class="row">
    <div class="col-md-12 col-sm-12 col-xs-12">
      <div class="info-box bg-orange">
        <span class="info-box-icon"><i class="fa fa-info"></i></span>
        <div class="info-box-content">
          <span class="info-box-text">Index status</span>
          <span class="info-box-number"><?php echo $snapshot->progress; ?>%</span>
          <div class="progress">
            <div class="progress-bar" style="width: <?php echo $snapshot->progress; ?>%"></div>
          </div>
          <span class="progress-description">
            <?php echo format_date($snapshot->created); ?>
          </span>
        </div>
      </div>
    </div>
  </div>
</section>
