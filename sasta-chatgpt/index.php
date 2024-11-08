<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>sasta chatgpt</title>
</head>
<body>

    <h1>Sasta ChatGPT</h1>
    
    <form method="POST">
        <label for="prompt">Ask Me Anything:</label>
        <input type="text" id="prompt" name="prompt" required>
        <button type="submit">you sure?</button>
    </form>

    <?php
    if ($_SERVER['REQUEST_METHOD'] == 'POST') {
        $input_prompt = escapeshellarg($_POST['prompt']); 

        $command = "./go.sh $input_prompt"; 

        exec($command, $output, $status);

        if ($status === 0) {
            echo "<h2>Shell Script Output:</h2>";

            $response = implode("\n", $output);
            if (preg_match('/"response":\s*"([^"]*)"/', $response, $matches)) {
                $formatted_response = wordwrap($matches[1], 50, "\n", true);
                echo "<pre>$formatted_response</pre>";
            } else {
                echo "<pre>Unable to parse response. Full output:</pre>";
                echo "<pre>" . htmlspecialchars($response) . "</pre>";
            }
        } else {
            echo "<h2>Error running the script</h2>";
            echo "<pre>Status Code: $status</pre>";
            echo "<pre>" . implode("\n", $output) . "</pre>";
        }
    }
    ?>

</body>
</html>
