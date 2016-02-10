<section class="content">
  <div class="row">
    <div class="col-md-3 col-sm-6 col-xs-12">
      <div class="info-box">
        <span class="info-box-icon bg-aqua"><i class="fa fa-download"></i></span>
        <div class="info-box-content">
          <span class="info-box-text">Downloads</span>
          <span class="info-box-number"><?php echo $project->downloads; ?></span>
        </div>
      </div>
    </div>
    <div class="col-md-3 col-sm-6 col-xs-12">
      <div class="info-box">
        <span class="info-box-icon bg-green"><i class="fa fa-users"></i></span>
        <div class="info-box-content">
          <span class="info-box-text">Users</span>
          <span class="info-box-number"><?php echo count($users); ?></span>
        </div>
        <!-- /.info-box-content -->
      </div>
    </div>
    <div class="col-md-3 col-sm-6 col-xs-12">
      <div class="info-box bg-yellow">
        <span class="info-box-icon"><i class="fa fa-comments-o"></i></span>
        <div class="info-box-content">
          <span class="info-box-text">Comments</span>
          <span class="info-box-number"><?php echo $comments->totalCount; ?></span>
          <div class="progress">
            <div class="progress-bar" style="width: 70%"></div>
          </div>
          <span class="progress-description">
            70% Increase in 30 Days
          </span>
        </div>
      </div>
    </div>
    <div class="col-md-3 col-sm-6 col-xs-12">
      <div class="info-box bg-red">
        <span class="info-box-icon"><i class="fa fa-star-o"></i></span>
        <div class="info-box-content">
          <span class="info-box-text">Issues</span>
          <span class="info-box-number"><?php echo $issues->totalCount ?></span>
          <div class="progress">
            <div class="progress-bar" style="width: <?php echo ($issues->totalCount) ? ($issues->closedCount * 100 / $issues->totalCount) : 0; ?>%"></div>
          </div>
          <span class="progress-description">
            <?php echo $issues->openCount ?> open issues
          </span>
        </div>
      </div>
    </div>
  </div>
  <!-- =========================================================== -->
  <div class="row">
    <div class="col-md-6 col-sm-6 col-xs-12">
      <div class="box box-solid bg-light-blue-gradient">
        <div class="box-header ui-sortable-handle">
          <i class="fa fa-map-marker"></i><h3 class="box-title">User Map</h3>
        </div>
        <div class="box-body">
          <div id="map-container" style="width: 100%; height: 300px;"></div>
        </div>
        <div class="box-footer no-border">
          <div class="row">
            <div class="col-xs-4 text-center" style="border-right: 1px solid #f4f4f4">
              <div id="sparkline-1"></div>
              <div class="knob-label">Total</div>
            </div>
            <div class="col-xs-4 text-center" style="border-right: 1px solid #f4f4f4">
              <div id="sparkline-2"></div>
              <div class="knob-label">Active</div>
            </div>
            <div class="col-xs-4 text-center">
              <div id="sparkline-3"></div>
              <div class="knob-label">Inactive</div>
            </div>
          </div>
        </div>
      </div>
    </div>
    <div class="col-md-6 col-sm-6 col-xs-12">
      <div class="box box-solid bg-light-blue-gradient">
        <div class="box-header ui-sortable-handle">
          <i class="fa fa-map-marker"></i><h3 class="box-title">User Demographics</h3>
        </div>
        <div class="box-body">
          <div id="user-container" style="width: 100%; height: 300px;"></div>
        </div>
      </div>
    </div>
  </div>
  <!-- /.row -->
  <!-- =========================================================== -->
  <!-- Small boxes (Stat box) -->
  <div class="row">
    <div class="col-lg-3 col-xs-6">
      <!-- small box -->
      <div class="small-box bg-aqua">
        <div class="inner">
          <h3>150</h3>
          <p>New Orders</p>
        </div>
        <div class="icon">
          <i class="fa fa-shopping-cart"></i>
        </div>
        <a href="#" class="small-box-footer">
          More info <i class="fa fa-arrow-circle-right"></i>
        </a>
      </div>
    </div>
    <!-- ./col -->
    <div class="col-lg-3 col-xs-6">
      <!-- small box -->
      <div class="small-box bg-green">
        <div class="inner">
          <h3>53<sup style="font-size: 20px">%</sup></h3>
          <p>Bounce Rate</p>
        </div>
        <div class="icon">
          <i class="ion ion-stats-bars"></i>
        </div>
        <a href="#" class="small-box-footer">
          More info <i class="fa fa-arrow-circle-right"></i>
        </a>
      </div>
    </div>
    <!-- ./col -->
    <div class="col-lg-3 col-xs-6">
      <!-- small box -->
      <div class="small-box bg-yellow">
        <div class="inner">
          <h3>44</h3>
          <p>User Registrations</p>
        </div>
        <div class="icon">
          <i class="ion ion-person-add"></i>
        </div>
        <a href="#" class="small-box-footer">
          More info <i class="fa fa-arrow-circle-right"></i>
        </a>
      </div>
    </div>
    <!-- ./col -->
    <div class="col-lg-3 col-xs-6">
      <!-- small box -->
      <div class="small-box bg-red">
        <div class="inner">
          <h3><?php echo $issues->openCount; ?></h3>
          <p>Open Issues</p>
        </div>
        <div class="icon">
          <i class="ion ion-pie-graph"></i>
        </div>
        <a href="https://www.drupal.org/project/issues/<?php echo $project->data->field_project_machine_name; ?>" target="_blank" class="small-box-footer">
          More info <i class="fa fa-arrow-circle-right"></i>
        </a>
      </div>
    </div>
    <!-- ./col -->
  </div>
  <!-- /.row -->
</section>
<script src="//cdnjs.cloudflare.com/ajax/libs/d3/3.5.3/d3.min.js"></script>
<script src="//cdnjs.cloudflare.com/ajax/libs/topojson/1.6.9/topojson.min.js"></script>
<script src="/sites/all/modules/development/projecthealth/js/datamaps.world.min.js"></script>
<script>
var map = new Datamap({
element: document.getElementById('map-container'),
fills: {
HIGH: '#aaaaff',
LOW: '#efefff',
MEDIUM: '#cdcdff',
UNKNOWN: 'rgb(0,0,0)',
defaultFill: '#ffffff'
},
data: {
IND: {
fillKey: 'LOW',
numberOfThings: 2002
},
USA: {
fillKey: 'MEDIUM',
numberOfThings: 10381
},
AUS: {
fillKey: 'HIGH',
numberOfThings: 10
}
},
geographyConfig: {
popupTemplate: function(geo, data) {
return ['<div class="hoverinfo"><strong>',
  'Number of things in ' + geo.properties.name,
  ': ' + data.numberOfThings,
'</strong></div>'].join('');
}
}
});
</script>
