<!doctype html>
<html lang="fr">
  <head>
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <!-- Bootstrap CSS -->
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.1/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-+0n0xVW2eSR5OomGNYDnhzAbDsOXxcvSN1TPprVMTNDbiYZCxYbOOl7+AMvyTG2x" crossorigin="anonymous">

    <title>Planning</title>
  </head>
  <body>
    <h2>Planning</h2>
        <p>Code couleur significatif sur le bilan des objectifs journaliers :</p>
        </br>
        <button type="button" class="btn btn-secondary">Jour à venir</button>
        <button type="button" class="btn btn-success">Objectif atteint</button>
        <button type="button" class="btn btn-danger">Objectif non atteint</button>
        <button type="button" class="btn btn-warning">Bilan mitigé</button>
        </br>
        </br>
        </br>
        <ul class="nav nav-tabs" id="myTab" role="tablist">
            <li class="nav-item" role="presentation">
              <button class="nav-link active" id="home-tab" data-bs-toggle="tab" data-bs-target="#home" type="button" role="tab" aria-controls="home" aria-selected="true">Du 14 au 18 juin</button>
            </li>
            <li class="nav-item" role="presentation">
              <button class="nav-link" id="profile-tab" data-bs-toggle="tab" data-bs-target="#profile" type="button" role="tab" aria-controls="profile" aria-selected="false">Du 21 au 24 juin</button>
            </li>
          </ul>
          <div class="tab-content" id="myTabContent">
            <div class="tab-pane fade show active" id="home" role="tabpanel" aria-labelledby="home-tab">
                <table class="table">
                    <thead class="table-light">
                      <tr>
                          <th>#</th>
                          <th>Lundi 14 juin</th>
                          <th>Mardi 15 juin</th>
                          <th>Mercredi 16 juin</th>
                          <th>Jeudi 17 juin</th>
                          <th>Vendredi 18 juin</th>
                      </tr>
                    </thead>
                    <tbody>
                        <tr>
                            <th>Matin</th>
                            <th>
                                <?php
                                    include 'jours/14mat.php';
                                ?>
                            </th>
                            <th>
                                <?php
                                    include 'jours/15mat.php';
                                ?>
                            </th>
                            <th>
                                <?php
                                    include 'jours/16mat.php';
                                ?>
                            </th>
                            <th>
                                <?php
                                    include 'jours/17mat.php';
                                ?>
                            </th>
                            <th>
                                <?php
                                    include 'jours/18mat.php';
                                ?>
                            </th>
                        </tr>

                        <tr>
                            <th>Après-midi</th>
                            <th>
                                <?php
                                    include 'jours/14ap.php';
                                ?>
                            </th>
                            <th>
                                <?php
                                    include 'jours/15ap.php';
                                ?>
                            </th>
                            <th>
                                <?php
                                    include 'jours/16ap.php';
                                ?>
                            </th>
                            <th>
                                <?php
                                    include 'jours/17ap.php';
                                ?>
                            </th>
                            <th>
                                <?php
                                    include 'jours/18ap.php';
                                ?>
                            </th>
                        </tr>
                        
                        
                    </tbody>
                  </table>
            </div>
            <div class="tab-pane fade" id="profile" role="tabpanel" aria-labelledby="profile-tab">
                <table class="table">
                    <thead class="table-light">
                      <tr>
                          <th>#</th>
                          <th>Lundi</th>
                          <th>Mardi</th>
                          <th>Mercredi</th>
                          <th>Jeudi</th>
                          <th>Vendredi</th>
                      </tr>
                    </thead>
                    <tbody>
                        <tr>
                            <th>Matin</th>
                            <th>
                                <button type="button" class="btn btn-success" data-bs-toggle="modal" data-bs-target="#exampleModal">
                                    Voir
                                </button>
                            </th>
                            <th>
                                <button type="button" class="btn btn-success" data-bs-toggle="modal" data-bs-target="#exampleModal">
                                    Voir
                                </button>
                            </th>
                            <th>
                                <button type="button" class="btn btn-danger" data-bs-toggle="modal" data-bs-target="#exampleModal">
                                    Voir
                                </button>
                            </th>
                            <th>
                                <button type="button" class="btn btn-danger" data-bs-toggle="modal" data-bs-target="#exampleModal">
                                    Voir
                                </button>
                            </th>
                            <th>
                                <button type="button" class="btn btn-danger" data-bs-toggle="modal" data-bs-target="#exampleModal">
                                    Voir
                                </button>
                            </th>
                        </tr>
                        <tr>
                            <th>Après-Midi</th>
                            <th>
                                <button type="button" class="btn btn-success" data-bs-toggle="modal" data-bs-target="#exampleModal">
                                    Voir
                                </button>
                            </th>
                            <th>
                                <button type="button" class="btn btn-success" data-bs-toggle="modal" data-bs-target="#exampleModal">
                                    Voir
                                </button>
                            </th>
                            <th>
                                <button type="button" class="btn btn-success" data-bs-toggle="modal" data-bs-target="#exampleModal">
                                    Voir
                                </button>
                            </th>
                            <th>
                                <button type="button" class="btn btn-success" data-bs-toggle="modal" data-bs-target="#exampleModal">
                                    Voir
                                </button>
                            </th>
                            <th>
                                <button type="button" class="btn btn-success" data-bs-toggle="modal" data-bs-target="#exampleModal">
                                    Voir
                                </button>
                            </th>
                        </tr>
                        
                    </tbody>
                  </table>
            </div>
          </div>          
    <!-- Optional JavaScript; choose one of the two! -->

    <!-- Option 1: Bootstrap Bundle with Popper -->
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.1/dist/js/bootstrap.bundle.min.js" integrity="sha384-gtEjrD/SeCtmISkJkNUaaKMoLD0//ElJ19smozuHV6z3Iehds+3Ulb9Bn9Plx0x4" crossorigin="anonymous"></script>

    <!-- Option 2: Separate Popper and Bootstrap JS -->
    <!--
    <script src="https://cdn.jsdelivr.net/npm/@popperjs/core@2.9.2/dist/umd/popper.min.js" integrity="sha384-IQsoLXl5PILFhosVNubq5LC7Qb9DXgDA9i+tQ8Zj3iwWAwPtgFTxbJ8NT4GN1R8p" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.1/dist/js/bootstrap.min.js" integrity="sha384-Atwg2Pkwv9vp0ygtn1JAojH0nYbwNJLPhwyoVbhoPwBhjQPR5VtM2+xf0Uwh9KtT" crossorigin="anonymous"></script>
    -->
  </body>
</html>
