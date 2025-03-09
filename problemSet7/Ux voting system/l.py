
def determine_outcome(m, preferences):
    # Initialize the possible states (NNN, NNY, NYN, NYY, YNN, YNY, YYN, YYY)
    states = ['NNN', 'NNY', 'NYN', 'NYY', 'YNN', 'YNY', 'YYN', 'YYY']
    
    # Create a dictionary to map states to their index
    state_to_index = {state: idx for idx, state in enumerate(states)}
    
    # Initialize the final outcome for each state
    final_outcome = [None] * 8
    
    # Start from the last priest and move backwards
    for priest in range(m-1, -1, -1):
        current_preferences = preferences[priest]
        new_final_outcome = [None] * 8
        
        for state_idx in range(8):
            current_state = states[state_idx]
            best_outcome = None
            best_preference = float('inf')
            
            # Try flipping each stone
            for flip in range(3):
                new_state = list(current_state)
                new_state[flip] = 'Y' if new_state[flip] == 'N' else 'N'
                new_state = ''.join(new_state)
                new_state_idx = state_to_index[new_state]
                
                # Get the outcome after this flip
                outcome = final_outcome[new_state_idx] if priest != m-1 else new_state
                preference = current_preferences[state_to_index[outcome]]
                
                if preference < best_preference:
                    best_preference = preference
                    best_outcome = outcome
            
            new_final_outcome[state_idx] = best_outcome
        
        final_outcome = new_final_outcome
    
    # The initial state is NNN
    return final_outcome[state_to_index['NNN']]

# Read input
n = int(input())
for _ in range(n):
    m = int(input())
    preferences = []
    for _ in range(m):
        preference_order = list(map(int, input().split()))
        preferences.append(preference_order)
    
    outcome = determine_outcome(m, preferences)
    print(outcome)

