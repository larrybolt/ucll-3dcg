Dir['*.rb'].select do |file|
  # Select all test generating ruby files
  /-tests\.rb$/ =~ file
end.each do |file|
  require "./#{file}"
end
